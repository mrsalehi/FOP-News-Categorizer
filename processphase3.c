int process(int *occurrence,news **Category_Root,news **News_Root,int *Category_Number)
{
    FILE *Content_File; Content_File=fopen("content.txt","r");

    char *Data_In_Line = malloc (1000*sizeof (char));
    char *title = malloc (500*sizeof (char));
    char *description = malloc (1000*sizeof (char));
    char *category = malloc (20*sizeof (char));
    char *space = malloc (sizeof (char));space=" ";
    char *Tmp_String = malloc (1000*sizeof (char));

    int isFound_description=0,isFound_title=0,isFound_category=0;

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

            else if (Data_In_Line[2]=='<' && Data_In_Line[3]=='c' &&
                     Data_In_Line[4]=='a'&& Data_In_Line[5]=='t'&& Data_In_Line[6]=='e' && Data_In_Line[7]=='g' &&
                     Data_In_Line[8]=='o'&& Data_In_Line[9]=='r'&& Data_In_Line[10]=='y'&& Data_In_Line[11]=='>')
            {
                isFound_category=1;
                fgets(Data_In_Line,1000,Content_File);
                strcpy(category, categoryAnalyse(Data_In_Line));
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

        if (isFound_category==1 && isFound_description==1 && isFound_title==1)
        {
            if(strcmp(category,"business")==0)
            {
                splitFunc (Category_Root[BUSINESS_NUMBER],News_Root[News_Number],description,title);
                occurrence[BUSINESS_NUMBER]++;
                Category_Number[News_Number]=BUSINESS_NUMBER;
            }
            else if(strcmp(category,"world")==0)
            {
                splitFunc (Category_Root[WORLD_NUMBER],News_Root[News_Number],description,title);
                occurrence[WORLD_NUMBER]++;
                Category_Number[News_Number]=WORLD_NUMBER;
            }
            else if(strcmp(category,"sci_tech")==0)
            {
                splitFunc (Category_Root[SCITECH_NUMBER],News_Root[News_Number],description,title);
                occurrence[SCITECH_NUMBER]++;
                Category_Number[News_Number]=SCITECH_NUMBER;
            }
            else if(strcmp(category,"health")==0)
            {
                splitFunc (Category_Root[HEALTH_NUMBER],News_Root[News_Number],description,title);
                occurrence[HEALTH_NUMBER]++;
                Category_Number[News_Number]=HEALTH_NUMBER;
            }
            else if(strcmp(category,"entertainment")==0)
            {
                splitFunc (Category_Root[ENTERTAINMENT_NUMBER],News_Root[News_Number],description,title);
                occurrence[ENTERTAINMENT_NUMBER]++;
                Category_Number[News_Number]=ENTERTAINMENT_NUMBER;
            }
            else if (strcmp(category,"us")==0)
            {
                splitFunc (Category_Root[US_NUMBER],News_Root[News_Number],description,title);
                occurrence[US_NUMBER]++;
                Category_Number[News_Number]=US_NUMBER;
            }
            else if (strcmp(category,"sport")==0)
            {
                splitFunc (Category_Root[SPORT_NUMBER],News_Root[News_Number],description,title);
                occurrence[SPORT_NUMBER]++;
                Category_Number[News_Number]=SPORT_NUMBER;
            }
            isFound_category=0;isFound_description=0;isFound_title=0;
            News_Number++;
        }
    }
    fclose (Content_File);
    return 0;
}
///------------------------------------------------------------------------------------------------------------
char* titleAnalyse(char *title)
{
    int indicator=0;
    int tag=0;
    int result_length=0;
    int data_length=0;

    char *result=malloc (strlen(title)*sizeof (char));

    while(indicator<strlen(title))
    {
        if (title[indicator]=='<')
            tag=1;
        if (title[indicator]=='>')
            tag=0;

        if (title[indicator]!='>' && title[indicator]!='<' && tag==0 && title[indicator]!='\r' &&
            title[indicator]!='\t' && title[indicator]!='\n')
        {
            if (uncategorized==true)
            {
                data.title[data_length]=title[indicator];
                data_length++;
                data.title[data_length]='\0';
            }
            if ((title[indicator]>='a' && title[indicator]<='z') || title[indicator]==' ')
            {
                result[result_length]=title[indicator];
                result_length++;
                result[result_length]='\0';
            }
            else if (title[indicator]>='A' && title[indicator]<='Z')
            {
                result[result_length]=(char)((int)title[indicator]+32);
                result_length++;
                result[result_length]='\0';
            }
        }
        indicator++;
    }
    strcat (title," ");

    return result;
}
//--------------------------------------------------------------------------------------------------
char* categoryAnalyse(char *category)
{
    int indicator=0;
    int Tag_Number=0;
    int Bracket_Number=0;
    int result_length=0;

    char *result=malloc (strlen(category)* sizeof (char));


    while(indicator<strlen(category))
    {
        if (category[indicator]=='[')
            Bracket_Number++;
        if (category[indicator]=='<')
            Tag_Number++;


        if (category[indicator]!=']' && category[indicator]!='[' && Bracket_Number==2 && Tag_Number==1 && category[indicator]!='\r' &&
            category[indicator]!='\t' && category[indicator]!='\n' && category[indicator]!='<' && category[indicator]!='>' &&
            category[indicator]!=' ')
        {
            result[result_length]=category[indicator];
            result_length++;
            result[result_length]='\0';
        }

        indicator++;
    }
    return result;
}
//---------------------------------------------------------------------------------------------------
char* descriptionAnalyse(char *description)
{
    int bracket=0;
    int indicator=0;
    int tag=0;
    int result_length=0;
    int data_length=0;
    char *result=malloc (strlen(description) * sizeof (char));
    result[0]='\0';

    while(indicator<strlen(description))
    {
        if (description[indicator]=='[')
            bracket++;
        if (description[indicator]==']')
            bracket--;

        if (description[indicator]=='<')
            tag++;
        if (description[indicator]=='>')
            tag--;


        if (description[indicator]!='>' && description[indicator]!='<' && bracket==2 && tag<2 && description[indicator]!='[' &&
            description[indicator]!=']' && description[indicator]!='\r' && description[indicator]!='\t' &&
            description[indicator]!='\n' && description[indicator]!='"')
        {
            if (uncategorized==true)
            {
                data.description[data_length]=description[indicator];
                data_length++;
                data.description[data_length]='\0';
            }
            if ((description[indicator]>='a' && description[indicator]<='z') || description[indicator]==' ')
            {
                result[result_length]=description[indicator];
                result_length++;
                result[result_length]='\0';
            }
            else if (description[indicator]>='A' && description[indicator]<='Z')
            {
                result[result_length]=(char)((int)description[indicator]+32);
                result_length++;
                result[result_length]='\0';
            }
        }
        indicator++;
    }
    if (result[0]!='\0')
        strcat(result," ");

    return result;
}
void dateAnalyse(char *pubDate)
{
    int indicator=0;
    int tag=0;
    int result_length=0;

    while(indicator<strlen(pubDate))
    {
        if (pubDate[indicator]=='<')
            tag=1;

        if (pubDate[indicator]=='>')
            tag=0;

        if (pubDate[indicator]!='>' && pubDate[indicator]!='<' && tag==0 && pubDate[indicator]!='\r' &&
             pubDate[indicator]!='\t' && pubDate[indicator]!='\n')
        {
            data.pubDate[result_length]=pubDate[indicator];
            result_length++;
            data.pubDate[result_length]='\0';
        }
        indicator++;
    }
}
