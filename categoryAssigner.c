#include "header.h"
#include "getphase3.c"
#include "processphase3.c"
#include "preProcessphase3.c"

void splitFuncUncategorized (news *news_root,char *description,char *title)
{
    int index;
    int indicator=0;
    int Result_Length=0;

    char *result = malloc (500 * sizeof (char));

    int i=0;

    while (indicator<strlen(description))
    {
         if (description[indicator]==' ')
        {
            index=(int)result[0];
            if (index>=97 && index<=122)
                insert(news_root,result);

            Result_Length=0;
            result[0]='\0';
        }
        else if (description[indicator]>='a' && description[indicator]<='z')
        {
            result[Result_Length]=description[indicator];
            Result_Length++;
            result[Result_Length]='\0';
        }
        indicator++;
    }

    result[0]='\0';
    indicator=0;
    Result_Length=0;

    while (indicator<strlen(title))
    {
        if (title[indicator]==' ')
        {
            index=(int)result[0];
            if (index>=97 && index<=122)
                insert(news_root,result);


        }
        else if (title[indicator]>='a' && title[indicator]<='z')
        {
            result[Result_Length]=title[indicator];
            Result_Length++;
            result[Result_Length]='\0';
        }
        indicator++;
    }
}
///------------------------------------------------------------------------
int main()
{
    getURLS();

    int *Category_Number=malloc (30000 * sizeof (int));

    int i;
//-----------------------------------------------------------
    news **News_Root=malloc (30000*sizeof (news*));
    for (i=0;i<30000;i++)
        News_Root[i]=(news*)getNode();
//----------------------------
    news **Uncategorized_Root = malloc ( 2000 * sizeof (news*));
    for (i=0;i<2000;i++)
        Uncategorized_Root[i]=(news*)getNode();
//----------------------------
    news **Category_Root=malloc (7 * sizeof (news*));
    for (i=0;i<7;i++)
        Category_Root[i] = (news *)getNode();

    preProcess(Category_Root,News_Root,Category_Number);

    double **News_Weight=malloc (News_Number * sizeof (double*));
    for (i=0;i<News_Number;i++)
        News_Weight[i]=malloc (FINAL_NUMBER * sizeof (double));

    double **Category_Weight=malloc (7 * sizeof (double*));
    for (i=0;i<7;i++)
        Category_Weight[i]= calloc (FINAL_NUMBER , sizeof (double));

    for (i=0;i<News_Number;i++)
    {
        vectorBuilder(News_Root[i],Category_Number,Category_Weight,News_Weight,i,News_Number,FINAL_NUMBER,0);
    }

    uncategorized=true;

    readUncategorizedNews(Uncategorized_Root);

    double **uncategorizedNews_Weight=malloc (uncategorizedNews_Number * sizeof (double*));

    for (i=0;i<uncategorizedNews_Number;i++)
        uncategorizedNews_Weight[i]=malloc (FINAL_NUMBER * sizeof (double));


    for (i=0;i<uncategorizedNews_Number;i++)
    {
        vectorBuilder(Uncategorized_Root[i],Category_Number,Category_Weight,uncategorizedNews_Weight,i,News_Number,FINAL_NUMBER,1);
    }
//--------------------------------------------
    double max;
    int j;
    for (i=0;i<uncategorizedNews_Number;i++)
    {
        max=dot(uncategorizedNews_Weight,Category_Weight,i,0,FINAL_NUMBER);
        Category_Number[i]=0;
        for (j=1;j<7;j++)
            if (dot(uncategorizedNews_Weight,Category_Weight,i,j,FINAL_NUMBER) > max)
            {
                Category_Number[i]=j;
                max=dot(uncategorizedNews_Weight,Category_Weight,i,j,FINAL_NUMBER);
            }
    }
//    for (i=0;i<uncategorizedNews_Number;i++)
//        printf ("%d: %d\n",i,Category_Number[i]);

//    FILE *f=fopen ("categories.txt","w");
//    int t;
//    for (i=0;i<uncategorizedNews_Number;i++)
//    {
//        t=Category_Number[i];
//        if (t==0)
//            fprintf (f,"business");
//        else if (t==1)
//            fprintf (f,"world");
//        else if (t==2)
//            fprintf (f,"sci_tech");
//        else if (t==3)
//            fprintf (f,"health");
//        else if (t==4)
//            fprintf (f,"entertainment");
//        else if (t==5)
//            fprintf (f,"us");
//        else if (t==6)
//            fprintf (f,"sport");
//        fprintf (f," ");
//    }
//    fclose (f);
    jsonMaker(Category_Number);
}
///----------------------------------------------------------------------------------------------------------
void vectorBuilder (news *news_root,int *Category_Number,double **Category_Weight,double **weight,int num,int News_Number,int Final_Number,bool uncategorized)
{
    int i;
    int occurrence;
    double Temp_Weight;

    for(i=0;i<Final_Number;i++)
    {
        occurrence=search(news_root,word[i].name);
        Temp_Weight=(double)occurrence * log((double)News_Number/word[i].occurrence);
        weight[num][i]=Temp_Weight;

        if (uncategorized==false)
            Category_Weight[Category_Number[num]][i]+=weight[num][i];
    }
}
///----------------------------------------------------------------------------------------------------------
double dot(double **uncategorizedNews_Weight,double **Category_Weight,int News_Index,int Category_Index,int Final_Number)
{
    int i;
    double dot=0.0;
    double News_Magnitude=0.0;
    double Category_Magnitude;

    for (i=0;i<Final_Number;i++)
    {
        dot+=(double)uncategorizedNews_Weight[News_Index][i] * Category_Weight[Category_Index][i];
    }
    return dot;
}
///----------------------------------------------------------------------------------------------------------
int readUncategorizedNews(news **Uncategorized_Root)
{
    FILE *Content_File=fopen ("uncategorizedNews.txt","r");

    char *Data_In_Line = malloc (3000*sizeof (char));
    char *title = malloc (500*sizeof (char));
    char *description = malloc (3000*sizeof (char));
    char *Tmp_String = malloc (3000*sizeof (char));

    int isFound_description=0,isFound_title=0,isFound_pubDate=0;

    while(fgets(Data_In_Line,2000,Content_File)!=NULL)
    {
        if (Data_In_Line[0]=='\t' && Data_In_Line[1]=='\t')
        {

            if (Data_In_Line[2]=='<' && Data_In_Line[3]=='t' && Data_In_Line[4]=='i'&& Data_In_Line[5]=='t'&&
                Data_In_Line[6]=='l'&& Data_In_Line[7]=='e' && Data_In_Line[8]=='>')
            {
                isFound_title=1;
                strcpy(title,titleAnalyse(Data_In_Line));
            }
            else if (Data_In_Line[2]=='<' && Data_In_Line[3]=='p' && Data_In_Line[4]=='u'&& Data_In_Line[5]=='b'&&
                     Data_In_Line[6]=='D'&& Data_In_Line[7]=='a'&& Data_In_Line[8]=='t'&& Data_In_Line[9]=='e')
            {
                isFound_pubDate=1;
                dateAnalyse(Data_In_Line);
            }

            else if (Data_In_Line[2]=='<' && Data_In_Line[3]=='d' && Data_In_Line[4]=='e' && Data_In_Line[5]=='s' &&
                     Data_In_Line[6]=='c' && Data_In_Line[7]=='r' && Data_In_Line[8]=='i' &&Data_In_Line[9]=='p' &&
                     Data_In_Line[10]=='t' && Data_In_Line[11]=='i' && Data_In_Line[12]=='o'&& Data_In_Line[13]=='n'&&
                     Data_In_Line[14]=='>')
            {
                fgets(Data_In_Line,2000,Content_File);
                while(Data_In_Line[strlen(Data_In_Line)-3]!='n' || Data_In_Line[strlen(Data_In_Line)-2]!='>')
                {
                    Tmp_String=malloc (2000*sizeof (char));
                    Tmp_String[0]='\0';
                    strcpy(Tmp_String,Data_In_Line);
                    fgets(Data_In_Line,2000,Content_File);
                    strcat(Tmp_String,Data_In_Line);
                    strcpy(Data_In_Line,Tmp_String);
                }
                isFound_description=1;
                strcpy(description,descriptionAnalyse(Data_In_Line));
            }
        }

        if (isFound_description==1 && isFound_title==1 && isFound_pubDate==1)
        {
            splitFuncUncategorized (Uncategorized_Root[uncategorizedNews_Number],description,title);
            isFound_description=0;isFound_title=0;isFound_pubDate=0;

            strcpy (description,data.description);
            strcpy (title,data.title);
            strcpy (Tmp_String,data.pubDate);

            writeProcessedDataInFile(title,description,Tmp_String);
            uncategorizedNews_Number++;
        }
    }

    fclose (Content_File);
    return 0;
}
///-----------------------------------------------------------------------------
void writeProcessedDataInFile(char *title,char *description,char *pubDate)
{
    FILE *data;
    data=fopen("finalized.txt","a");
    fprintf(data,title);fprintf (data,"\",\n");
    fprintf (data,pubDate);fprintf (data,"\",\n");
    fprintf(data,description);fprintf (data,"\",\n");
    fclose(data);
}

