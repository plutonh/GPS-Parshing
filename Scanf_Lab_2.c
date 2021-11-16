void GPS_type_GGA(char * Data_receive,struct Ele_Num GGAN)
{
	int Comma_cnt=0, i, j;
	for(i=0;i<strlen(Data_receive);i++)
	{
		if(Data_receive[i]==',')
			Comma_cnt++;	
	}
	if(Comma_cnt!=14)
	{
		HAMSTERTONGUE_Debugf("Data was damagegd\n");
	}
	else
	{
		printf("%d\n", GGAN.num);
		for(i=0;i<GGAN.num-1;i++)
		{
			if(i==5||i==6||i==7||i==9)
			{
				for(j=GGAN.Element[i];j<GGAN.Element[i+1]-1;j++)
					HAMSTERTONGUE_Debugf("%c ", Data_receive[j]);
			}
		}
        printf("\n");
	}
}

void GPS_type_GLL(char * Data_receive,struct Ele_Num GLLN)
{
	int Comma_cnt=0, i, j;
	for(i=0;i<strlen(Data_receive);i++)
	{
		if(Data_receive[i]==',')
			Comma_cnt++;	
	}
	if(Comma_cnt!=7)
	{
		HAMSTERTONGUE_Debugf("Data was damagegd\n");
	}
	else
	{
		printf("%d\n", GLLN.num);
		for(i=0;i<GLLN.num-1;i++)
		{
			if(i==1||i==2||i==3||i==4)
			{
				for(j=GLLN.Element[i];j<GLLN.Element[i+1]-1;j++)
					HAMSTERTONGUE_Debugf("%c ", Data_receive[j]);
			}
		}
        printf("\n");
	}
}

void Split(char *Data_receive)
{
    int Data_cnt = 0, Ele_cnt = 1, i, start, len=0;
    char GPS_Type[4];
    struct Ele_Num Ele;
    Ele.Element[0]=0;
    while (1)
    {
        if (Data_receive[Data_cnt] == ',')
        {
            Ele.Element[Ele_cnt] = Data_cnt + 1;
            Ele_cnt++;
            if(Data_receive[Data_cnt+1]==',')
            	Data_cnt++;
        }
        len++;
        if(len==strlen(Data_receive))
        	break;
        Data_cnt++;
    }
    for(i=0;i<3;i++)
    	GPS_Type[i]=Data_receive[i+2];
	Ele.num = Ele_cnt;
    HAMSTERTONGUE_Debugf("parser calling, elecnt=%d", Ele.num);
	if(strcmp(GPS_Type,"GGA")==0)
	{
		GPS_type_GGA(Data_receive,Ele);	
	}		
	else if(strcmp(GPS_Type,"GLL")==0)
	{
		GPS_type_GLL(Data_receive,Ele);
	}
}

int tskParsingGPS(int argc, char *argv[])
{
    #define MSG_BUF_SIZE 32
    char buf[MSG_BUF_SIZE];
    char Assemble_Data[100]={0,};
    char Splited_Data[100]={0,};
    int ret, reterr, i, k=0, Data_len, Data_start, Data_end, Data_split=0, Condition=0;
    struct Ele_Num Ele;
    mqd_t mq = mq_open("/mqgps", O_RDWR);
    HAMSTERTONGUE_Debugf("mq opened : %d", mq);
    while(1) { 
        ret = mq_receive(mq, buf, MSG_BUF_SIZE, NULL);
        HAMSTERTONGUE_Debugf("mq_received, ret=%d", ret);
        strcat(Assemble_Data,buf);
        Data_len=strlen(Assemble_Data);
        for(i=0;i<Data_len;i++)
        {
            
        	if(Assemble_Data[i]=='$')
        	{
        		if(Data_split==1)
        		{
        			Data_end=i;
        			Condition=1;
        			break;
				}
				else
				{
					Data_split=1;
					Data_start=i+1;
				}
			}
		}
        HAMSTERTONGUE_Debugf("Data_len=%d, Condition=%d", Data_len, Condition);
		if(Condition==1)
		{

			for(i=0; i<Data_end-Data_start;i++)
				Splited_Data[i]=Assemble_Data[Data_start+i];
			for(i=0;i<Data_len;i++)
			{
				if(i<Data_len-Data_end)
				{
					Assemble_Data[i]=Assemble_Data[Data_end+k];
					k++;
				}
				else
					Assemble_Data[i]='\0';
			}
            HAMSTERTONGUE_Debugf("Split calling, i=%d", i);
        	Split(Splited_Data);
            usleep(1000000); 
		}
		Data_split=0;
		Condition=0;
		k=0;
    } 
}