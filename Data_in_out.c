#include <stdio.h>
#include <string.h>
#define MAX 10000
#define true 1
#define false 0

int front = -1;
int rear = -1;
char queue[MAX];

struct Ele_Num {
    int Element[50];
    int num;
};

struct Exm_end {
    char Easm[200];
    int end;
};

int IsEmpty(void)
{
    if (front == rear)
        return true;
    else
        return false;
}

int IsFull(void)
{
    int tmp = (rear + 1) % MAX;
    if (tmp == front)
        return true;
    else
        return false;
}

void addq(char* value, int num)
{
    int i;
    if (IsFull())
        printf("Queue is Full.\n");
    else
    {
        for (i = 0; i < num; i++)
        {
            rear = (rear + 1) % MAX;
            queue[rear] = value[i];
        }
    }
}

char deq()
{
    if (IsEmpty())
        return '\0';
    else
    {
        front = (front + 1) % MAX;
        return queue[front];
    }
}

struct Exm_end Assemble()
{
    char rev;
    char sum[200]={0,};
    struct Exm_end Exm;
    int cnt = 0, i;
    while (1)
    {
        rev = deq();
        if (rev == '$')
        {
            Exm.end = 0;
            break;
        }
        else if (rev == '\0')
        {
            Exm.end = -1;
            break;
        }
        else
        {
            sum[cnt] = rev;
            cnt++;
            Exm.end = 0;
        }
    }
    for(i=0;i<cnt;i++)
		Exm.Easm[i]=sum[i];
	for(i=cnt;i<200;i++)
		Exm.Easm[i]='\0';
    return Exm;
}

struct Ele_Num Split(char *Data_receive)//데이터 값을 ','에 따라 분리 
{
    int Data_cnt = 0, Ele_cnt = 1;
    struct Ele_Num Ele;
    Ele.Element[0]=0;
    while (1)
    {
        if (Data_receive[Data_cnt] == ',')
        {
            Ele.Element[Ele_cnt] = Data_cnt + 1;
            Ele_cnt++;
        }
        else if (Data_receive[Data_cnt] == NULL)
        {
        	Ele.Element[Ele_cnt] = Data_cnt;
        	break;
		}
        Data_cnt++;
    }
    Ele.num = Ele_cnt;
    return Ele;
}

GPS_type_GGA(struct Exm_end GGAE,struct Ele_Num GGAN)
{
	int j, k=0;
	for (j = 0; j <= GGAN.num; j++)
    {
        while(k < GGAN.Element[j])
        {
        	printf("%c", GGAE.Easm[k]);
        	k++;
		}
		k = GGAN.Element[j];
		printf("\n");
	}
    printf("\n");
}

GPS_type_GLL(struct Exm_end GLLE,struct Ele_Num GLLN)
{
	int j, k=0;
	for (j = 0; j <= GLLN.num; j++)
    {
        while(k < GLLN.Element[j])
        {
        	printf("%c", GLLE.Easm[k]);
        	k++;
		}
		k = GLLN.Element[j];
		printf("\n");
	}
    printf("\n");
}

GPS_type_GSA(struct Exm_end GSAE,struct Ele_Num GSAN)
{
	int j, k=0;
	for (j = 0; j <= GSAN.num; j++)
    {
        while(k < GSAN.Element[j])
        {
        	printf("%c", GSAE.Easm[k]);
        	k++;
		}
		k = GSAN.Element[j];
		printf("\n");
	}
    printf("\n");
}

GPS_type_GSV(struct Exm_end GSVE,struct Ele_Num GSVN)
{
	int j, k=0;
	for (j = 0; j <= GSVN.num; j++)
    {
        while(k < GSVN.Element[j])
        {
        	printf("%c", GSVE.Easm[k]);
        	k++;
		}
		k = GSVN.Element[j];
		printf("\n");
	}
    printf("\n");
}

GPS_type_RMC(struct Exm_end RMCE,struct Ele_Num RMCN)
{
	int j, k=0;
	for (j = 0; j <= RMCN.num; j++)
    {
        while(k < RMCN.Element[j])
        {
        	printf("%c", RMCE.Easm[k]);
        	k++;
		}
		k = RMCN.Element[j];
		printf("\n");
	}
    printf("\n");
}

GPS_type_VTG(struct Exm_end VTGE,struct Ele_Num VTGN)
{
	int j, k=0;
	for (j = 0; j <= VTGN.num; j++)
    {
        while(k < VTGN.Element[j])
        {
        	printf("%c", VTGE.Easm[k]);
        	k++;
		}
		k = VTGN.Element[j];
		printf("\n");
	}
    printf("\n");
}

GPS_type_ZDA(struct Exm_end ZDAE,struct Ele_Num ZDAN)
{
	int j, k=0;
	for (j = 0; j <= ZDAN.num; j++)
    {
        while(k < ZDAN.Element[j])
        {
        	printf("%c", ZDAE.Easm[k]);
        	k++;
		}
		k = ZDAN.Element[j];
		printf("\n");
	}
    printf("\n");
}

int main(void)
{
    char Data_receive[200];
    char *Data_trans;
    char GPS_type[3]={0,};
    struct Exm_end Exm;
    struct Ele_Num Ele;
    int i, j, k=0, num_in, num_out, con=0;
    scanf("%d", &num_in);
    scanf("%d", &num_out);
    for (i = 0; i < num_in; i++)
    {
        scanf("%s", Data_receive, sizeof(Data_receive));
        addq(Data_receive, strlen(Data_receive));
    }
    for (i = 0; i < num_out; i++)
    {
        Exm = Assemble();
        Data_trans=Exm.Easm;
        Ele = Split(Data_trans);
        con=Exm.end;
        for(j=0;j<3;j++)
			GPS_type[j]=Exm.Easm[j+2];
		if(strcmp(GPS_type,"GGA")==0)
		{
			GPS_type_GGA(Exm,Ele);
		}				
		else if(strcmp(GPS_type,"GLL")==0)
		{
			GPS_type_GLL(Exm,Ele);
		}
		else if(strcmp(GPS_type,"GSA")==0)
		{
			GPS_type_GSA(Exm,Ele);
		}
		else if(strcmp(GPS_type,"GSV")==0)
		{
			GPS_type_GSV(Exm,Ele);
		}
		else if(strcmp(GPS_type,"RMC")==0)
		{
			GPS_type_RMC(Exm,Ele);
		}
		else if(strcmp(GPS_type,"VTG")==0)
		{
			GPS_type_VTG(Exm,Ele);
		}
		else if(strcmp(GPS_type,"ZDA")==0)
		{
			GPS_type_ZDA(Exm,Ele);
		}
		else
		{
			printf("Data was damaged\n");
		}
		if (con == -1)
    	{
        	printf("Queue is Empty\n");
        	break;
    	}
    }
    return 0;
}
