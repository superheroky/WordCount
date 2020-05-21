#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define DEF_MODER S_IRUSR|S_IRGRP|S_IROTH
#define DEF_MODEW S_IWUSR|S_IWGRP|S_IWOTH
#define Maxchar (4096)
void * Readfile(int fd);
int Charnum(char * instr);

int Wordnum(char* str);
int Linenum(char* str);
void Outfd(int argc, char **argv,char**output);

int main(int argc,char **argv)
{
    if(argc < 3)
    {
        printf("使用方法");
        exit(0);
    }
    int l=0,w=0,c=0;
    char* inputfile;
    char* outputfile;
    int infd,outfd;
    char instr[Maxchar];
    char outstr[Maxchar];
    //printf("%s %s",argv[1],argv[2]);
    //exit(0);
    for(int count = 1; count < argc; count++)
    {
        //判断必需参数
        if(!strcmp(argv[count], "-c"))
        {
            c = 1;
            //Method1
        }
        else if(!strcmp(argv[count] ,"-w"))
        {
            w = 1;
        }
        else if(!strcmp(argv[count] ,"-l"))
        {
            l = 1;
        }
        else
        {
        //搜索输入文件名
            inputfile = argv[count];
            break;
        }

    }

    //读出字符串
    FILE * fpread;
    FILE * fpwrite;
    fpread = fopen(inputfile,"r");
    fread(instr,sizeof(char),Maxchar,fpread);
    fclose(fpread);



    //计算统计结果
    if(c)
        sprintf(outstr,"%s 字符数: %d\n\n",inputfile,Charnum(instr));
    if(w)
        sprintf(outstr,"%s%s 字母数: %d\n\n",outstr,inputfile,Wordnum(instr));
    if(l)
        sprintf(outstr,"%s%s   行数: %d\n\n",outstr,inputfile,Linenum(instr));
    printf("%s\n",outstr);


    //输出
    Outfd(argc,argv,&outputfile);

    fpwrite = fopen(outputfile,"w+");
    fwrite(outstr,sizeof(char),strlen(outstr),fpwrite);
    fclose(fpwrite);
}

//read file
void * Readfile(int fd)
{
    void * buf = (void *)malloc(sizeof(char)*Maxchar);
    size_t maxchar = Maxchar;
    if(read(fd,buf,maxchar)<0)
    {
        fprintf(stderr,"error");
        exit(0);
    }
    return buf;
}
int Charnum(char* str)
{
    int totalchar=0;
    while(*str++ != '\0')
    {
        totalchar++;
    }
    return totalchar;

}
int Wordnum(char* str)
{
    char*  currpt;
    int count=0;
    while(*str != '\0')
    {

        if(!(((*str>=0x41)&&(*str<=0x5A))||((*str>=0x61)&&(*str<=0x7A))))
        {
            str++;
            continue;
        }
        else
        {
            currpt = str+1;
            do
            {
                if(!(((*currpt>=0x41)&&(*currpt<=0x5A))||((*currpt>=0x61)&&(*currpt<=0x7A))))
                {
                    count++;
                    str = currpt;
                    break;
                }

            }while(*(++currpt) != '\0');
        }


    }
    return count;

}

int Linenum(char* str)
{
    int linenum = 0;
    while(*str != '\0')
    {
        if(*str++ == '\n')
        linenum++;
    }
    return linenum;

}
void Outfd(int argc, char **argv,char**output)
{
    char *outfile = "Outfile";
    FILE *fp;
        //搜索 "-o"
    if(!strcmp(argv[argc-2] ,"-o"))
    {
        if(argv[argc-1] != NULL)
        {
            //strcpy(outfile,argv[argc-1]);
            outfile = argv[argc-1];
       }
        else
            fprintf(stderr,"no out file exit");
    }
    *output = outfile;

}
