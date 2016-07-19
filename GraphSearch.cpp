
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define maxsrcnum 100
#define maxwordnum 200
#define minwordnum 100
#define DICLEN  10001
#define GRALEN  4000000
#define length 200
#define maxpath 10
typedef char gstring[maxwordnum+1];
typedef char sstring[maxwordnum+1];/****************************************************************************************************************************/
typedef _int64 path[maxpath+1];
typedef struct listss
{
	sstring k[5];
	int num;
}listss;               //分搜索关键字
typedef struct node
{
	sstring data;
	struct node* next;
	sstring fdata;
	_int64 order;
}node;                //哈希表结点（链表示法）
typedef struct hashtable
{
	node* phead;
	node** chainhash;
}hashtable;           //哈希表
typedef struct ArcNode
{
	_int64 adjvex;
	struct ArcNode *nextarc;
}ArcNode;            //图结点
typedef struct VNode
{
	gstring data;
	int type;
	sstring fdata;
	ArcNode* firstarc;
}VNode,AdjList[GRALEN];     //图定点
typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;
	//int kind;
}ALGraph;              //图



 _int64 sum=0;
 _int64 sumi=0;
 _int64 sumo=0;
sstring RDFind={'R','D','F','i','n','d'};
sstring GraphSearch={'G','r','a','p','h','S','e','a','r','c','h'};
int smorder[20];
hashtable* graph;
ALGraph G;
path pathx;
listss keyx;
int visited[GRALEN]={0};
_int64 BKDRhash(sstring s)
{
	//printf("\ns=%s",s);
	//printf("ai0 ");
	_int64 seed=131;
	_int64 hash=0;
	int num=strlen(s);
	int i=0;
	//printf("ai1 ");
	while(s[i]!=(char)10&&s[i]!='\0')
	{
	//	printf("ai1.5 ");
		hash=hash+s[i];
		
	//	printf("hash=%I64d ",hash);
		i++;
	//	printf("ai2 ");
	}
	//printf("ai2.5 ");
//	printf("%I64d",hash%DICLEN);
	return hash%DICLEN;
}
node* create_node()
{//开辟节点
	node* pnode = (node*)malloc(sizeof(node));
	memset(pnode, 0, sizeof(node));
	
//	memset(pnode->data, 0, 300 * sizeof(char));
	pnode->next = NULL;
	
	return pnode;
}
hashtable* create_hash()
{//创建hash表
//	printf("ek0");
	hashtable* new_hash_table = (hashtable*)malloc(sizeof(hashtable));
	memset(new_hash_table, 0, sizeof(hashtable));
	
	new_hash_table->phead = create_node();
	new_hash_table->chainhash = (node**)malloc(DICLEN * sizeof(node*));
//	printf("ek1");
	for(int i = 0; i <=DICLEN; i++){        
		new_hash_table->chainhash[i] = (node*)malloc(sizeof(node));
		memset(new_hash_table->chainhash[i], 0, sizeof(node));
	}
//	printf("ek2");
	return new_hash_table;
}
int insert_data(hashtable* hash, node* phead, sstring data,sstring fdata)
{//插入新数据
//	printf("%I64d ",sum);
//	if(sum%1000000==0&&sum>=1000000)
//	{
//		printf("%d complete!",sum/1000000);
//	}
	sum++;
	if(hash == NULL)
	{
//		printf("go0");

		return 0;
	}
	
	if(hash->chainhash[BKDRhash(data)]->data == NULL){
//		printf("in");
		node* newnode = create_node();
		
		strcpy(newnode->data, data);
		strcpy(newnode->fdata,fdata);
		newnode->next = NULL;
		strcpy(hash->chainhash[BKDRhash(data)]->data,newnode->data);
		strcpy(hash->chainhash[BKDRhash(data)]->fdata,newnode->fdata);
		hash->chainhash[BKDRhash(data)]->order=sumo;
	//	printf("#@%s %I64d#\n",newnode->data,sumo);
		hash->chainhash[BKDRhash(data)]->next = newnode->next;
		
		free(newnode);
		return 1;
	}
	else{     
	//	printf("in2");
		phead = hash->chainhash[BKDRhash(data)];
	//	printf(" %I64d ",BKDRhash(data));
	//	printf("in3");
		while(phead->next != NULL)
			phead = phead->next;
	//	printf("4");
		phead->next = create_node();
//		printf("5");
		strcpy(phead->next->data, data);
//		printf("6");
		strcpy(phead->next->fdata,fdata);
		phead->next->order=sumo;
	//	printf("#%s %I64d#\n",data,sumo);
//		printf("7");
		phead->next->next = NULL;
//		printf("8");
		return 1;
	}
}
node* find_data(hashtable* hash, node* phead, sstring data,sstring StrLine2)
{//查找数据
	phead = hash->chainhash[BKDRhash(data)];
	sstring StrLine22;
	strcpy(StrLine22,StrLine2);
	StrLine22[strlen(StrLine22)-1]='\0';
	if(hash == NULL)
		return NULL;
	
	while(phead != NULL){
		
		if(strcmp(phead->data, data) == 0)
		{	//return phead;
			node* judge=phead;
			if(judge!=NULL)
			{
				if(strcmp(StrLine2,judge->fdata)!=0)
				{
					sstring StrLine3;
					strcpy(StrLine3,judge->fdata);
					//StrLine2[strlen(StrLine2)-1]='\0';
					StrLine3[strlen(StrLine3)-1]='\0';
					printf("%s %s\n",StrLine3,StrLine22);
				}
				
			}
			phead=phead->next;
			//free(judge);
		}

		else
			phead = phead->next;
	}
//	printf("fuck!");
	//free(StrLine22);
	//printf("kao!");
	return NULL;
}
int find_data2(hashtable* hash, node* phead, sstring data,sstring StrLine2)
{//查找数据
	int i=0;
	phead = hash->chainhash[BKDRhash(data)];
//	sstring StrLine22;
//	strcpy(StrLine22,StrLine2);
//	StrLine22[strlen(StrLine22)-1]='\0';
	if(hash == NULL)
		return 0;
	
	while(phead != NULL){
		
		if(strcmp(phead->data, data) == 0)
		{	//return phead;
			return 1;

		//	phead=phead->next;
			//free(judge);
		}

		else
			phead = phead->next;
	}
//	printf("fuck!");
	//free(StrLine22);
	//printf("kao!");

	return 0;
}
node* find_data3(hashtable* hash, node* phead, gstring data)
  {//查找数据
      phead = hash->chainhash[BKDRhash(data)];

      if(hash == NULL)
          return NULL;

      while(phead != NULL){

         if(strcmp(phead->data, data) == 0)
             return phead;
         else
             phead = phead->next;
     }

     return NULL;
 }
void change(sstring s)
{
	int num,i;
	num=strlen(s);
	for(i=num;i>=1;i--)
	{
		s[i]=s[i-1];
	}
	s[num+1]='\0';
	s[0]=num;
}	
void returnchange(sstring s)
{
	int num,i;
	num=strlen(s)-1;
	for(i=1;i<=num;i++)
	{
		s[i-1]=s[i];
	}
	s[num]='\0';
}
void getnextval(sstring t,int nextval[])
{
	//sstring p;
	int i=1,j=0,num=strlen(t);
	nextval[1]=0;
	while(i<=num)
	{
		if(j==0||t[i]==t[j])
		{
			i++;j++;
			if(t[i]!=t[j])
			nextval[i]=j;
			else
			nextval[i]=nextval[j];

		}
		else
		{
			j=nextval[j];
		}
	}
}
int check_kmp(sstring s,sstring t,int pos,int end)
{
//	printf("t=====%s",t);
	//printf("in");
	change(s);
	change(t);
	int nextval[300];/****************************************************************************************************************************/
	getnextval(t,nextval);
	int i,j,num1,num2;
	i=pos;
	j=1;
	num1=strlen(s)-1;
	num2=strlen(t)-1;
	//printf("num2=%d\n",num2);
//	printf("in!");
	while(i<=num1&&j<=num2)
	{
		if(i>end) return 0;
		if(j==0||s[i]==t[j])
		{
			i++;j++;
			//if(j!=1)
			//printf("$%d$%c=$%d$%c\n",i-1,s[i-1],j-1,t[j-1]);
		}
		else
		{
		//	printf("*");
			j=nextval[j];
		}
	}
	returnchange(s);
	returnchange(t);
	if(j>num2)
	{
		//printf(" i find it ");
	//	printf("I find it at %d\n",i-num2);
		return 1;
	}
	else
	{
			//printf("un!");
	//	printf("I can't find it\n");
		return 0;
	}
}

int lcheck_kmp(sstring s,listss key,int pos,int end)
{
	if(key.num==0)
	return 1;     //直接保送通过
	int i;
	for(i=0;i<key.num;i++)
	{
		if(!check_kmp(s,key.k[i],pos,end))
		return 0;
	}
	return 1;
}
int wcheck_kmp(sstring s,sstring t,int pos,int end)
{
	//printf("in");
	change(s);
	change(t);
	int nextval[300];/****************************************************************************************************************************/
	getnextval(t,nextval);
	int i,j,num1,num2;
	i=pos;      
	j=1;                       
	num1=strlen(s)-1;
	num2=strlen(t)-1;
//	printf("in!");
	while(i<=num1&&j<=num2)
	{
		if(i>end) return 0;
		if(j==0||s[i]==t[j])
		{
			i++;j++;
		}
		else
		{
			j=nextval[j];
		}
	}
	i--;
	returnchange(s);
	returnchange(t);
	if(j>num2)
	{
		//printf(" i find it ");
	//	printf("I find it at %d\n",i-num2);
//		printf("###########%c########",s[i]);
		if(i<=end&&((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z')))
		{
	//		printf("###########%c########",s[i]);
			return 0;
		}
		if(i-num2-1>=pos&&((s[i-num2-1]>='A'&&s[i-num2-1]<='Z')||(s[i-num2-1]>='a'&&s[i-num2-1]<='z')))
		{
			return 0;
		}
		return 1;
	}
	else
	{
			//printf("un!");
	//	printf("I can't find it\n");
		return 0;
	}
}

int wlcheck_kmp(sstring s,listss key,int pos,int end)
{
	if(key.num==0)
	return 1;     //直接保送通过
	int i;
	for(i=0;i<key.num;i++)
	{
		if(!wcheck_kmp(s,key.k[i],pos,end))
		return 0;
	}
	return 1;
}
int getsmorder(int smorder[],int argc,char *argv[])
{
	int i;
	for(i=0;i<=10;i++)
	{
		smorder[i]=-1;
	}
	if(!strcmp(RDFind,argv[1]))
	{
		smorder[0]=1;
	}
	for(i=0;i<argc;i++)
	{
		if(argv[i][0]=='-'&&argv[i][1]=='s')  //-s
		smorder[1]=i;   //返回所在位置
		if(argv[i][0]=='-'&&argv[i][1]=='p')  //-p
		smorder[2]=i;   
		if(argv[i][0]=='-'&&argv[i][1]=='o')  //-o
		smorder[3]=i;
		if(argv[i][0]=='-'&&argv[i][1]=='w')  //-w
		smorder[4]=i;
		if(argv[i][0]=='-'&&argv[i][1]=='j'&&argv[i][2]=='1')  //-j1
		smorder[5]=i;
		if(argv[i][0]=='-'&&argv[i][1]=='j'&&argv[i][2]=='2')  //-j2
		smorder[6]=i;
		if(argv[i][0]=='-'&&argv[i][1]=='j'&&argv[i][2]=='3')  //-j3
		smorder[7]=i;
		if(argv[i][0]=='-'&&argv[i][1]=='j'&&argv[i][2]=='4')  //-j4
		smorder[8]=i;
	}
	return 1;
}
int getkey(listss &key,char *argv[],int i) // i是关键字所在位置                                  i是引号后边的第一个字符下标，返回末尾引号下标。
{
	if(i==0)     //根本没有这部分的关键字
	{
		key.num=0;
		return -1;
	}                        //以上一定要改
	int fi=0,j=i;
	i=0;
	key.num=0;
	while(1)
	{
		if(argv[j][i]==' '||argv[j][i]=='\0')
		{
			strncpy(key.k[key.num],argv[j]+fi,i-fi);
			key.k[key.num][i-fi]='\0';
			key.num++;
			fi=i+1;
		}
		if(argv[j][i]=='\0') break;
		i++;
	}
	return i;
}
void getsrc(int argc,char *argv[],sstring &src)
{
	strcpy(src,argv[argc-1]);
}
void getthreedots(sstring StrLine,int &s1,int &e1,int &s2,int &e2,int &s3,int &e3)  
{
	int i=0;
	s1=0;
	while(StrLine[i]!=(char)9)
	{
		i++;
	}
	e1=i-1;
	while(StrLine[i]==(char)9)
	{
		i++;
	}
	s2=i;
	while(StrLine[i]!=(char)9)
	{
		i++;
	}
	e2=i-1;
	while(StrLine[i]==(char)9)
	{
		i++;
	}
	s3=i;
	while(StrLine[i]!=(char)9&&StrLine[i]!=(char)10)
	{
		i++;
	}
	e3=i-1;
}
void insertnode(ALGraph &G,hashtable* dic,_int64 i,gstring s)
{
	if(G.vertices[i].firstarc==NULL)
	{
		ArcNode* an=(ArcNode*)malloc(sizeof(ArcNode));
		an->adjvex=find_data3(dic,dic->phead,s)->order;
		an->nextarc=NULL;
		G.vertices[i].firstarc=an;
		an=NULL;
		free(an);
	}
	else
	{
		ArcNode* an=G.vertices[i].firstarc;
		while(an->nextarc!=NULL)
		{
			an=an->nextarc;
		}
		ArcNode* un=(ArcNode*)malloc(sizeof(ArcNode));
		un->adjvex=find_data3(dic,dic->phead,s)->order;
		un->nextarc=NULL;
		an->nextarc=un;
		an=NULL;
		un=NULL;
		free(an);
		free(un);
	}
}
void DFS(_int64 start,int floor,int terminal)
{
//	printf("in");
	int i;
	pathx[floor]=start;
	visited[start]=1;
	if(floor<=terminal)
	{
		if(lcheck_kmp(G.vertices[start].data,keyx,0,strlen(G.vertices[start].data)))
		{
			for(i=0;i<=floor;i++)
			{
				if(i==floor)
				{
					printf("%s",G.vertices[pathx[i]].fdata);
				}
				else
				printf("%s -> ",G.vertices[pathx[i]].fdata);
			}
			return ;
		}
		if(floor==terminal)
		{
			return ;
		}
	}
	ArcNode* p;
	for(p=G.vertices[start].firstarc;p!=NULL;p=p->nextarc)
	{
		_int64 w=p->adjvex;
		if(!visited[w])
		{
			DFS(w,floor+1,terminal);
		}
	}
	p=NULL;
	free(p);
}

int ReadSpeacialLine(int argc, char *argv[]) 
{ 
//	printf("go");
    //sstring filename ;//文件名
	//sstring string; //词语
//	sstring order;
//	int smorder[20];
	//printf("please input the src of your File: ");
	//scanf("%s",filename);
	//printf("please input the word you wanna to find: ");
	//gets(string);
	// scanf("%s",string);
	//printf("please input the order:");
//	gets(order);
//	getsmorder(smorder,order);
	if(!strcmp(RDFind,argv[0]))
	{
		if(smorder[1]==-1&&smorder[2]==-1&&smorder[3]==-1&&smorder[4]==-1&&smorder[5]==-1&&smorder[6]==-1&&smorder[7]==-1&&smorder[8]==-1)        //任务1
		{
			printf("haha");
			int i=8,fi=8,j=0;
			listss key;
			/*key.num=0;
			while(1)
			{
				if(order[i]==' '||order[i]==(char)34)
				{
					strncpy(key.k[key.num],order+fi,i-fi);
					key.k[key.num][i-fi]='\0';
					key.num++;
					fi=i+1;
				}
				if(order[i]==(char)34) break;
				i++;
			}*/
			getkey(key,argv,1);
			printf("%s",key.k[0]);
			//printf("key.num=%d\n",key.num);
			sstring src;
			getsrc(argc,argv,src);
		//	printf("%s",src);
			/*while(order[i]!='\0')
			{
				src[j]=order[i];
				j++;i++;
			}
			src[j]='\0';*/

			/*for(i=0;i<key.num;i++)
			{
				printf("%s\n",key.k[i]);
			}*/
/**********************************************   以下是套路的逐行搜索       **************************************************/
			FILE *fp; 
			_int64 CurrentIndex=0;             //当前读取的行
			sstring StrLine;             //每行最大读取的字符数,可根据实际情况扩大
			if((fp = fopen(src,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			while (!feof(fp)) 
			{
				//sum++;
				fgets(StrLine,200,fp);//读取一行
				//  printf("on");
				//  printf("   is #%s#\n",StrLine);
			//	printf("the number of %s is %d\n",StrLine,strlen(StrLine));
				int s1,e1,s2,e2,s3,e3;
				getthreedots(StrLine,s1,e1,s2,e2,s3,e3);
			//	printf("s1=%d e1=%d s2=%d e2=%d s3=%d e3=%d\n",s1,e1,s2,e2,s3,e3);
				if(lcheck_kmp(StrLine,key,0,strlen(StrLine)))
				{
				//	printf("at %I64d\n",CurrentIndex);
					printf("%s\n", StrLine); //输出
				//	return 1;	  
				}
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex);
				CurrentIndex++;
				// printf("pf");
			//	printf("%s", StrLine); //输出
			} 
			fclose(fp);                    //关闭文件
			return 1;
		}
		else if(smorder[4]==-1&&smorder[5]==-1&&smorder[6]==-1&&smorder[7]==-1&&smorder[8]==-1&&(smorder[1]!=-1||smorder[2]!=-1||smorder[3]!=-1))  //任务2   普通版                                   //任务2
		{
			printf("hehe");
			listss key1,key2,key3;
			sstring src;
			int i,j=0;
			//将命令中三个位置对应生成三个key。
			getkey(key1,argv,smorder[1]+1);
			printf("%s",key1.k[0]);
			getkey(key2,argv,smorder[2]+1);
			getkey(key3,argv,smorder[3]+1);
			//找到src
			getsrc(argc,argv,src);
			//把三元组分开，找到三个起始位置 这一步要在每个进行细分Strline，用函数。
			FILE *fp; 
			_int64 CurrentIndex=0;             //当前读取的行
			sstring StrLine;             //每行最大读取的字符数,可根据实际情况扩大
			if((fp = fopen(src,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			while (!feof(fp)) 
			{
				//sum++;
				fgets(StrLine,200,fp);//读取一行
				//  printf("on");
				//  printf("   is #%s#\n",StrLine);
				int s1,e1,s2,e2,s3,e3;
				getthreedots(StrLine,s1,e1,s2,e2,s3,e3);
				if(lcheck_kmp(StrLine,key1,s1+1,e1+1)&&lcheck_kmp(StrLine,key2,s2+1,e2+1)&&lcheck_kmp(StrLine,key3,s3+1,e3+1))
				{
				//	printf("at %I64d\n",CurrentIndex);
					printf("%s\n", StrLine); //输出
				//	return 1;	  
				}
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex);
				CurrentIndex++;
				// printf("pf");
			//	printf("#%s#", StrLine); //输出
			} 
			fclose(fp);                    //关闭文件	
			//三个key拿去分别在对应位置进行check
			//如果并没有其中一个部分，那么生成的关键字数为0,直接check通过。
			return 1;
		}
		else if(smorder[4]!=-1&&smorder[5]==-1&&smorder[6]==-1&&smorder[7]==-1&&smorder[8]==-1&&(smorder[1]!=-1||smorder[2]!=-1||smorder[3]!=-1))  //任务2   -w版                                   //任务2
		{
		//	printf("hehe");
			listss key1,key2,key3;
			sstring src;
			int i,j=0;
			//将命令中三个位置对应生成三个key。
			getkey(key1,argv,smorder[1]+1);
			getkey(key2,argv,smorder[2]+1);
			getkey(key3,argv,smorder[3]+1);
			//找到src
			getsrc(argc,argv,src);
			//把三元组分开，找到三个起始位置 这一步要在每个进行细分Strline，用函数。
			FILE *fp; 
			_int64 CurrentIndex=0;             //当前读取的行
			sstring StrLine;             //每行最大读取的字符数,可根据实际情况扩大
			if((fp = fopen(src,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			while (!feof(fp)) 
			{
				//sum++;
				fgets(StrLine,200,fp);//读取一行
				//  printf("on");
				//  printf("   is #%s#\n",StrLine);
				int s1,e1,s2,e2,s3,e3;
				getthreedots(StrLine,s1,e1,s2,e2,s3,e3);
				if(wlcheck_kmp(StrLine,key1,s1+1,e1+1)&&wlcheck_kmp(StrLine,key2,s2+1,e2+1)&&wlcheck_kmp(StrLine,key3,s3+1,e3+1))
				{
				//	printf("at %I64d\n",CurrentIndex);
					printf("%s\n", StrLine); //输出
				//	return 1;	  
				}
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex);
				CurrentIndex++;
				// printf("pf");
			//	printf("#%s#", StrLine); //输出
			} 
			fclose(fp);                    //关闭文件	
			//三个key拿去分别在对应位置进行check
			//如果并没有其中一个部分，那么生成的关键字数为0,直接check通过。
			return 1;
		}
		else if(smorder[4]!=-1)          //任务3
		{
		//	printf("guagua");
			listss key;
			sstring src;
			getkey(key,argv,smorder[4]+1);
			getsrc(argc,argv,src);
				FILE *fp; 
			_int64 CurrentIndex=0;             //当前读取的行
			sstring StrLine;             //每行最大读取的字符数,可根据实际情况扩大
			if((fp = fopen(src,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			while (!feof(fp)) 
			{
				//sum++;
				fgets(StrLine,200,fp);//读取一行
				//  printf("on");
				//  printf("   is #%s#\n",StrLine);
				int s1,e1,s2,e2,s3,e3;
				getthreedots(StrLine,s1,e1,s2,e2,s3,e3);
				if(wlcheck_kmp(StrLine,key,0,strlen(StrLine)))
				{
				//	printf("at %I64d\n",CurrentIndex);
					printf("%s\n", StrLine); //输出
				//	return 1;	  
				}
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex);
				CurrentIndex++;
				// printf("pf");
			//	printf("#%s#", StrLine); //输出
			} 
			fclose(fp);                    //关闭文件
			return 1;
		}
		else if(smorder[5]!=-1)   //-j1
		{
			hashtable* dic=create_hash();
			//	printf("%s\n",argv[4]);
			//	printf("lala\n");
			sstring src1,src2;
			strcpy(src1,argv[2]);
			strcpy(src2,argv[3]);
		//	printf("%s\n",src1);
		//	printf("%s",src2);

			//打开一个文件逐行，拿出主语

			//每一行去打开另一个文件进行查找，拿出主语，进行比较
			//若主语相同比较整个三元组，满足条件则连起来输出来。
			FILE *fp1,*fp2; 
			_int64 CurrentIndex1=0,CurrentIndex2=0;             //当前读取的行
			sstring StrLine1,StrLine2;             //每行最大读取的字符数,可根据实际情况扩大
			if((fp1 = fopen(src1,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			if((fp2 = fopen(src2,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			while (!feof(fp1)) 
			{
				//sum++;
				fgets(StrLine1,200,fp1);//读取一行
				//  printf("on");
				//  printf("   is #%s#\n",StrLine);
				int s1,e1,s2,e2,s3,e3;
				getthreedots(StrLine1,s1,e1,s2,e2,s3,e3);
				sstring sp1;
				strncpy(sp1,StrLine1+s1,e1-s1+1); //sp1里面存找出来的主语
				sp1[e1-s1+1]='\0';
				insert_data(dic,dic->phead,sp1,StrLine1);
			/*	while(!feof(fp2))
				{
					fgets(StrLine2,1024,fp2);
					//printf("#%s#", StrLine2);
					int ss1,ee1,ss2,ee2,ss3,ee3;
					getthreedots(StrLine2,ss1,ee1,ss2,ee2,ss3,ee3);
					sstring sp2;
					strncpy(sp2,StrLine2+ss1,ee1-ss1+1);
					sp2[ee1-ss1+1]='\0';
					if(strcmp(sp1,sp2)==0&&strcmp(StrLine1,StrLine2)!=0)
					{
						StrLine1[strlen(StrLine1)-1]='\0';
						StrLine2[strlen(StrLine2)-1]='\0';
						printf("%s   %s\n",StrLine1,StrLine2);
					}
					CurrentIndex2++;
				//	printf("%I64d %I64d\n",CurrentIndex1,CurrentIndex2);
				} 
				rewind(fp2);
				CurrentIndex2=0;*/
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex1);
				CurrentIndex1++;
				// printf("pf");
			//	printf("#%s#", StrLine1); //输出
			} 
			//printf("good table!");
			while(!feof(fp2))
			{
				fgets(StrLine2,200,fp2);//读取一行
				int ss1,ee1,ss2,ee2,ss3,ee3;
				getthreedots(StrLine2,ss1,ee1,ss2,ee2,ss3,ee3);
				sstring sp2;
				strncpy(sp2,StrLine2+ss1,ee1-ss1+1);
				sp2[ee1-ss1+1]='\0';
				find_data(dic,dic->phead,sp2,StrLine2);
				/*if(judge!=NULL)
				{
					if(strcmp(StrLine2,judge->fdata)!=0)
					{
						sstring StrLine3;
						strcpy(StrLine3,judge->fdata);
						StrLine2[strlen(StrLine2)-1]='\0';
						StrLine3[strlen(StrLine3)-1]='\0';
						printf("%s %s\n",StrLine3,StrLine2);
					}
	
				}*/
				CurrentIndex2++;
			}
			fclose(fp1);                    //关闭文件
			fclose(fp2);
		}
		else if(smorder[6]!=-1)   //-j2
		{

			hashtable* dic=create_hash();
		//	printf("%s\n",argv[4]);
		//	printf("lala\n");
			sstring src1,src2;
			strcpy(src1,argv[2]);
			strcpy(src2,argv[3]);
		//	printf("%s\n",src1);
		//	printf("%s",src2);

			//打开一个文件逐行，拿出主语

			//每一行去打开另一个文件进行查找，拿出主语，进行比较
			//若主语相同比较整个三元组，满足条件则连起来输出来。
			FILE *fp1,*fp2; 
			_int64 CurrentIndex1=0,CurrentIndex2=0;             //当前读取的行
			sstring StrLine1,StrLine2;             //每行最大读取的字符数,可根据实际情况扩大
			if((fp1 = fopen(src1,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			if((fp2 = fopen(src2,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			while (!feof(fp1)) 
			{
				//sum++;
				fgets(StrLine1,200,fp1);//读取一行
				//  printf("on");
				//  printf("   is #%s#\n",StrLine);
				int s1,e1,s2,e2,s3,e3;
				getthreedots(StrLine1,s1,e1,s2,e2,s3,e3);
				sstring sp1;
				strncpy(sp1,StrLine1+s3,e3-s3+1); //sp1里面存找出来的主语
				sp1[e3-s3+1]='\0';
				insert_data(dic,dic->phead,sp1,StrLine1);
			/*	while(!feof(fp2))
				{
					fgets(StrLine2,1024,fp2);
					//printf("#%s#", StrLine2);
					int ss1,ee1,ss2,ee2,ss3,ee3;
					getthreedots(StrLine2,ss1,ee1,ss2,ee2,ss3,ee3);
					sstring sp2;
					strncpy(sp2,StrLine2+ss1,ee1-ss1+1);
					sp2[ee1-ss1+1]='\0';
					if(strcmp(sp1,sp2)==0&&strcmp(StrLine1,StrLine2)!=0)
					{
						StrLine1[strlen(StrLine1)-1]='\0';
						StrLine2[strlen(StrLine2)-1]='\0';
						printf("%s   %s\n",StrLine1,StrLine2);
					}
					CurrentIndex2++;
				//	printf("%I64d %I64d\n",CurrentIndex1,CurrentIndex2);
				} 
				rewind(fp2);
				CurrentIndex2=0;*/
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex1);
				CurrentIndex1++;
				// printf("pf");
			//	printf("#%s#", StrLine1); //输出
			} 
			while(!feof(fp2))
			{
				fgets(StrLine2,200,fp2);//读取一行
				int ss1,ee1,ss2,ee2,ss3,ee3;
				getthreedots(StrLine2,ss1,ee1,ss2,ee2,ss3,ee3);
				sstring sp2;
				strncpy(sp2,StrLine2+ss3,ee3-ss3+1);
				sp2[ee3-ss3+1]='\0';
				find_data(dic,dic->phead,sp2,StrLine2);
				/*if(judge!=NULL)
				{
					if(strcmp(StrLine2,judge->fdata)!=0)
					{
						sstring StrLine3;
						strcpy(StrLine3,judge->fdata);
						StrLine2[strlen(StrLine2)-1]='\0';
						StrLine3[strlen(StrLine3)-1]='\0';
						printf("%s %s\n",StrLine3,StrLine2);
					}
	
				}*/
				CurrentIndex2++;
			}
			fclose(fp1);                    //关闭文件
			fclose(fp2);
		}
		else if(smorder[7]!=-1)   //-j3
		{
		
			hashtable* dic=create_hash();
		//	printf("%s\n",argv[4]);
		//	printf("lala\n");
			sstring src1,src2;
			strcpy(src1,argv[2]);
			strcpy(src2,argv[3]);
		//	printf("%s\n",src1);
		//	printf("%s",src2);

			//打开一个文件逐行，拿出主语

			//每一行去打开另一个文件进行查找，拿出主语，进行比较
			//若主语相同比较整个三元组，满足条件则连起来输出来。
			FILE *fp1,*fp2; 
			_int64 CurrentIndex1=0,CurrentIndex2=0;             //当前读取的行
			sstring StrLine1,StrLine2;             //每行最大读取的字符数,可根据实际情况扩大
			if((fp1 = fopen(src1,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			if((fp2 = fopen(src2,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			while (!feof(fp1)) 
			{
				//sum++;
				fgets(StrLine1,200,fp1);//读取一行
				//  printf("on");
				//  printf("   is #%s#\n",StrLine);
				int s1,e1,s2,e2,s3,e3;
				getthreedots(StrLine1,s1,e1,s2,e2,s3,e3);
				sstring sp1;
				strncpy(sp1,StrLine1+s1,e1-s1+1); //sp1里面存找出来的主语
				sp1[e1-s1+1]='\0';
				insert_data(dic,dic->phead,sp1,StrLine1);
			/*	while(!feof(fp2))
				{
					fgets(StrLine2,1024,fp2);
					//printf("#%s#", StrLine2);
					int ss1,ee1,ss2,ee2,ss3,ee3;
					getthreedots(StrLine2,ss1,ee1,ss2,ee2,ss3,ee3);
					sstring sp2;
					strncpy(sp2,StrLine2+ss1,ee1-ss1+1);
					sp2[ee1-ss1+1]='\0';
					if(strcmp(sp1,sp2)==0&&strcmp(StrLine1,StrLine2)!=0)
					{
						StrLine1[strlen(StrLine1)-1]='\0';
						StrLine2[strlen(StrLine2)-1]='\0';
						printf("%s   %s\n",StrLine1,StrLine2);
					}
					CurrentIndex2++;
				//	printf("%I64d %I64d\n",CurrentIndex1,CurrentIndex2);
				} 
				rewind(fp2);
				CurrentIndex2=0;*/
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex1);
				CurrentIndex1++;
				// printf("pf");
			//	printf("#%s#", StrLine1); //输出
			} 
			while(!feof(fp2))
			{
				fgets(StrLine2,200,fp2);//读取一行
				int ss1,ee1,ss2,ee2,ss3,ee3;
				getthreedots(StrLine2,ss1,ee1,ss2,ee2,ss3,ee3);
				sstring sp2;
				strncpy(sp2,StrLine2+ss3,ee3-ss3+1);
				sp2[ee3-ss3+1]='\0';
				find_data(dic,dic->phead,sp2,StrLine2);
				/*if(judge!=NULL)
				{
					if(strcmp(StrLine2,judge->fdata)!=0)
					{
						sstring StrLine3;
						strcpy(StrLine3,judge->fdata);
						StrLine2[strlen(StrLine2)-1]='\0';
						StrLine3[strlen(StrLine3)-1]='\0';
						printf("%s %s\n",StrLine3,StrLine2);
					}
	
				}*/
				CurrentIndex2++;
			}
			fclose(fp1);                    //关闭文件
			fclose(fp2);
		}
		else if(smorder[8]!=-1)   //-j4
		{
		
			hashtable* dic=create_hash();
		//	printf("%s\n",argv[4]);
		//	printf("lala\n");
			sstring src1,src2;
			strcpy(src1,argv[2]);
			strcpy(src2,argv[3]);
		//	printf("%s\n",src1);
		//	printf("%s",src2);

			//打开一个文件逐行，拿出主语

			//每一行去打开另一个文件进行查找，拿出主语，进行比较
			//若主语相同比较整个三元组，满足条件则连起来输出来。
			FILE *fp1,*fp2; 
			_int64 CurrentIndex1=0,CurrentIndex2=0;             //当前读取的行
			sstring StrLine1,StrLine2;             //每行最大读取的字符数,可根据实际情况扩大
			if((fp1 = fopen(src1,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			if((fp2 = fopen(src2,"r")) == NULL) //判断文件是否存在及可读
			{ 
				printf("error!"); 
				return 0; 
			} 
			while (!feof(fp1)) 
			{
				//sum++;
				fgets(StrLine1,200,fp1);//读取一行
				//  printf("on");
				//  printf("   is #%s#\n",StrLine);
				int s1,e1,s2,e2,s3,e3;
				getthreedots(StrLine1,s1,e1,s2,e2,s3,e3);
				sstring sp1;
				strncpy(sp1,StrLine1+s3,e3-s3+1); //sp1里面存找出来的主语
				sp1[e3-s3+1]='\0';
				insert_data(dic,dic->phead,sp1,StrLine1);
			/*	while(!feof(fp2))
				{
					fgets(StrLine2,1024,fp2);
					//printf("#%s#", StrLine2);
					int ss1,ee1,ss2,ee2,ss3,ee3;
					getthreedots(StrLine2,ss1,ee1,ss2,ee2,ss3,ee3);
					sstring sp2;
					strncpy(sp2,StrLine2+ss1,ee1-ss1+1);
					sp2[ee1-ss1+1]='\0';
					if(strcmp(sp1,sp2)==0&&strcmp(StrLine1,StrLine2)!=0)
					{
						StrLine1[strlen(StrLine1)-1]='\0';
						StrLine2[strlen(StrLine2)-1]='\0';
						printf("%s   %s\n",StrLine1,StrLine2);
					}
					CurrentIndex2++;
				//	printf("%I64d %I64d\n",CurrentIndex1,CurrentIndex2);
				} 
				rewind(fp2);
				CurrentIndex2=0;*/
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex1);
				CurrentIndex1++;
				// printf("pf");
			//	printf("#%s#", StrLine1); //输出
			} 
			while(!feof(fp2))
			{
				fgets(StrLine2,200,fp2);//读取一行
				int ss1,ee1,ss2,ee2,ss3,ee3;
				getthreedots(StrLine2,ss1,ee1,ss2,ee2,ss3,ee3);
				sstring sp2;
				strncpy(sp2,StrLine2+ss1,ee1-ss1+1);
				sp2[ee1-ss1+1]='\0';
				find_data(dic,dic->phead,sp2,StrLine2);
				/*if(judge!=NULL)
				{
					if(strcmp(StrLine2,judge->fdata)!=0)
					{
						sstring StrLine3;
						strcpy(StrLine3,judge->fdata);
						StrLine2[strlen(StrLine2)-1]='\0';
						StrLine3[strlen(StrLine3)-1]='\0';
						printf("%s %s\n",StrLine3,StrLine2);
					}
	
				}*/
				CurrentIndex2++;
			}
			fclose(fp1);                    //关闭文件
			fclose(fp2);
		}

		else
		{
			printf("over");
		}	
	}
	else if(!strcmp(GraphSearch,argv[0]))
	{
		//建图
		//广搜，若匹配则ok. 
		//建数组存搜索的路径
		//printf("yeah1");
		hashtable* dic=create_hash();
	//	printf("yeah1.2");
		sstring src;
		int i;
		getsrc(argc,argv,src);
		sstring st;
		strcpy(st,argv[1]);
		int step=argv[2][0]-'0';
		getkey(keyx,argv,3);
		FILE *fp; 
		_int64 CurrentIndex=0;             //当前读取的行
		sstring StrLine;             //每行最大读取的字符数,可根据实际情况扩大
		if((fp = fopen(src,"r")) == NULL) //判断文件是否存在及可读
		{ 
			printf("error!"); 
			return 0; 
		} 
	//	printf("yeah2");
		while (!feof(fp)) 
		{
			//sum++;
			fgets(StrLine,1024,fp);//读取一行
			//  printf("on");
			//  printf("   is #%s#\n",StrLine);
			//	printf("the number of %s is %d\n",StrLine,strlen(StrLine));
			int s1,e1,s2,e2,s3,e3;
			getthreedots(StrLine,s1,e1,s2,e2,s3,e3);
			if(StrLine[s3]!=(char)34&&StrLine[s3]!=(char)39)
			{
				sstring sp1;
				strncpy(sp1,StrLine+s1,e1-s1+1); //sp1里面存找出来的主语
				sp1[e1-s1+1]='\0';
				sstring sp2;
				strncpy(sp2,StrLine+s3,e3-s3+1);
				sp2[e3-s3+1]='\0';
				
				//	printf("s1=%d e1=%d s2=%d e2=%d s3=%d e3=%d\n",s1,e1,s2,e2,s3,e3);
				if(!find_data2(dic,dic->phead,sp1,StrLine))
				{
					sumo++;
					//	printf("%I64d ",sumo);
					insert_data(dic,dic->phead,sp1,StrLine);
					//	printf("at %I64d\n",CurrentIndex);
					//printf("%s\n", StrLine); //输出
					//	return 1;
					CurrentIndex++;
				}
				if(!find_data2(dic,dic->phead,sp2,StrLine))
				{
					sumo++;
					//	printf("%I64d ",sumo);
					insert_data(dic,dic->phead,sp2,StrLine);
					//	printf("at %I64d\n",CurrentIndex);
					//printf("%s\n", StrLine); //输出
					//	return 1;	 
					CurrentIndex++;
				}
			}
				  //printf("sumo=a%I64d",sumo);
			//           printf("%I64d\n",sum); //输出
			//读取一行,并定位到下一
			//	printf("%I64d",CurrentIndex);
			// printf("pf");
			//	printf("%s", StrLine); //输出
		} 
		//fclose(fp);                    //关闭文件
		//到这里已经建完哈希表并标数
		//遍历整个哈希表对图进行赋值
    	G.vexnum=0;
		G.arcnum=0;
		for(i=0;i<GRALEN;i++)
		{
			G.vertices[i].firstarc=NULL;
		}
		for(i=0;i<=DICLEN;i++)
		{
			if(dic->chainhash[i]->data == NULL)
			{
				continue;
			}
			else
			{     
				//	printf("in2");
				node* ph = dic->chainhash[i];
				while(ph->data!=NULL)
				{
					strcpy(G.vertices[ph->order].data,ph->data);
					strcpy(G.vertices[ph->order].fdata,ph->fdata);
					G.vertices[ph->order].firstarc=NULL;
				//	printf("data=%s order=%d\n",ph->data,ph->order);
					//G.vertices[ph->order].type
					//	printf(" %I64d ",BKDRhash(data));
					//	printf("in3");
					ph=ph->next;
					G.vexnum++;
				}//	printf("4");
				//phead->next = create_node();
				//		printf("5");
				//strcpy(phead->next->data, data);
				//		printf("6");
				//strcpy(phead->next->fdata,fdata);
				//		printf("7");
				//phead->next->next = NULL;
				//		printf("8");
				//return 1;
			}
		}//到这图初始化建好了
		rewind(fp);
		while (!feof(fp)) 
		{
			//sum++;
			fgets(StrLine,1024,fp);//读取一行
			//  printf("on");
			//  printf("   is #%s#\n",StrLine);
			//	printf("the number of %s is %d\n",StrLine,strlen(StrLine));
			int s1,e1,s2,e2,s3,e3;
			getthreedots(StrLine,s1,e1,s2,e2,s3,e3);
			if(StrLine[s3]!=(char)34&&StrLine[s3]!=(char)39)
			{
				sstring sp1;
				strncpy(sp1,StrLine+s1,e1-s1+1); //sp1里面存找出来的主语
				sp1[e1-s1+1]='\0';
				sstring sp2;
				strncpy(sp2,StrLine+s3,e3-s3+1);
				sp2[e3-s3+1]='\0';
				insertnode(G,dic,find_data3(dic,dic->phead,sp1)->order,sp2);
				insertnode(G,dic,find_data3(dic,dic->phead,sp2)->order,sp1);
				//	printf("s1=%d e1=%d s2=%d e2=%d s3=%d e3=%d\n",s1,e1,s2,e2,s3,e3);
				/*if(!find_data2(dic,dic->phead,sp1,StrLine))
				{
				sumo++;
				insert_data(dic,dic->phead,sp1,StrLine);
				//	printf("at %I64d\n",CurrentIndex);
				//printf("%s\n", StrLine); //输出
				//	return 1;	  
				}
				if(!find_data2(dic,dic->phead,sp2,StrLine))
				{
				sumo++;
				insert_data(dic,dic->phead,sp2,StrLine);
				//	printf("at %I64d\n",CurrentIndex);
				//printf("%s\n", StrLine); //输出
				//	return 1;	  
			}*/
				//	  printf("outf");
				//           printf("%I64d\n",sum); //输出
				//读取一行,并定位到下一
				//	printf("%I64d",CurrentIndex);
				CurrentIndex++;
			}
			// printf("pf");
			//	printf("%s", StrLine); //输出
		} 
		//遍历文件对图进行赋边
		//printf("bng!");
		//printf("the vexnum is %d\n",G.vexnum);
	//	printf("#%s#",G.vertices[5].data);
		G.vexnum=G.vexnum-DICLEN;
	
	//	printf("st=%s\n",st);
	//	printf("order=%I64d",find_data3(dic,dic->phead,st)->order);
	//	printf("here!");
	//	printf("%d",step);
		DFS(find_data3(dic,dic->phead,st)->order,0,step);
	}
	else
	{
	}
	return 0; 
}

int main(int argc, char *argv[])
{
//	printf("%s",argv[1]);
//	sstring testdata="I	love	apple\n";
	getsmorder(smorder,argc,argv);
//	printf("4");
//	for(int i=0;i<=8;i++)
//	{
//		printf("smorder%d=%d\n",i,smorder[i]);
//	}
//	printf("%c",argv[2][1]);
	ReadSpeacialLine(argc,argv);
/*	sstring a="ajdhsaohdaosbd";
	sstring b="bjdhsaohdaosbd";
	printf("%d",check_kmp(a,b,1,strlen(a)));  */
//	printf("%s",RDFind);
//	printf("ok0");
//	hashtable* dic=create_hash();
	/*FILE *fp; 
	_int64 CurrentIndex=0;             //当前读取的行
	sstring StrLine;             //每行最大读取的字符数,可根据实际情况扩大
	if((fp = fopen(argv[1],"r")) == NULL) //判断文件是否存在及可读
	{ 
		printf("error!"); 
		return 0; 
	} 
	//int s1,e1,s2,e2,s3,e3;
	while (!feof(fp)) 
	{
		fgets(StrLine,1024,fp);*///读取一行
		//getthreedots(StrLine,s1,e1,s2,e2,s3,e3);
	//if(StrLine[s3]!=(char)34&&StrLine[s3]!=(char)39)
	//	sumi++;
	/*	CurrentIndex++;
	}
		printf("%I64d",CurrentIndex);
			fclose(fp);*/
		//sum++;
		//printf("%I64d",CurrentIndex);
		//  printf("on");
		//  printf("   is #%s#\n",StrLine);
	//	if(lcheck_kmp(StrLine,key1,s1+1,e1+1)&&lcheck_kmp(StrLine,key2,s2+1,e2+1)&&lcheck_kmp(StrLine,key3,s3+1,e3+1))
		//{
			//	printf("at %I64d\n",CurrentIndex);
		//	printf("%s\n", StrLine); //输出
			//	return 1;	  
	//	}
	//	printf("%s\n",StrLine);
		//insert_data(dic,dic->phead,StrLine);
		//	  printf("outf");
		//           printf("%I64d\n",sum); //输出
		//读取一行,并定位到下一
		//	printf("%I64d",CurrentIndex);
		// printf("pf");
		//	printf("#%s#", StrLine); //输出
//	if(find_data(dic,dic->phead,testdata)!=NULL)
//	{
//		printf("find it:%s\n",find_data(dic,dic->phead,testdata));
//	}
//	else
	//{
//		printf("no this data\n");
//	}                   //关闭文件
//	printf("ok");
//	free(dic);
	//return 0;
//	graph=create_hash();
	return 0;
}

//小问题末尾的第四个功能显示不全