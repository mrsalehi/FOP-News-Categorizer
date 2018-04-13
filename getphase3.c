struct NewsData data;
//
extern bool uncategorized=false;
extern int News_Number=0;
extern int uncategorizedNews_Number=0;
extern int indicatorToWord=0;
///--------------------------------------------------------------------------------
void getURLS()
{
    FILE* f;
    f = fopen("text.txt","w");

    CURL *curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "http://team17:95105573_95105681@www.fop-project.ir/news/get-urls/?phase=3");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    fprintf(f," ");
    fclose(f);

    getRSS();
}
///------------------------------------------------------------------------------
void getRSS()
{
    FILE *Content_File;
    FILE *Url_File;

    Content_File = fopen("UncategorizedNews.txt","w");
    Url_File=fopen ("text.txt","r");

    char *url=malloc (300*sizeof (char));

    while(fscanf(Url_File,"%s",url)==1)
    {

        CURL *curl;
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL,url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, Content_File);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        fprintf (Content_File,"\n");
    }
    fclose(Url_File);
    fclose (Content_File);
}
///-----------------------------------------------------------------------------------
void jsonMaker(int *Category_Number)
{
    char *title=malloc (100*sizeof (char));title = "\"title\": ";
    char *description=malloc (100*sizeof (char));description="\"description\": ";
    char *category=malloc (100*sizeof (char));category="\"categories\": ";
    char *date=malloc (100*sizeof (char));date="\"date\": ";
    char *categorized=malloc (100*sizeof (char));categorized="\"categorized\": false";
    char *Tmp_String=malloc (4000 * sizeof (char));

    char *doubleQuote=malloc (sizeof (char));doubleQuote="\"";
    char *comma=malloc (sizeof (char));comma=",";
    char *open_bracket=malloc (sizeof (char));open_bracket="[";
    char *closed_bracket=malloc (sizeof (char));closed_bracket="]";
    char *closed_brace=malloc (sizeof (char));closed_brace="}";
    char *open_brace=malloc (sizeof (char));open_brace="{";
    char *nextLine=malloc (sizeof (char));nextLine="\n";

    char *result=malloc (5000*sizeof (char));

    FILE *data;
    data=fopen("finalized.txt","r");

    int i;
    for (i=0;i<uncategorizedNews_Number;i++)
    {
        result[0]='\0';

        fgets(Tmp_String,3000,data);

        strcat(result,open_brace);strcat(result,nextLine);
        //
        strcat(result,title);strcat(result,doubleQuote);strcat(result,Tmp_String);
        //
        fgets(Tmp_String,3000,data);
        //
        strcat(result,date);strcat(result,doubleQuote);strcat(result,Tmp_String);
        //
        fgets(Tmp_String,3000,data);
        //
        strcat(result,description);strcat(result,doubleQuote);strcat(result,Tmp_String);
        //
        strcat(result,categorized);
        //
        strcat(result,comma);strcat(result,nextLine);
        //
        strcat(result,category);strcat(result,open_bracket);strcat (result,doubleQuote);
        //


        int tmp=Category_Number[i];
        if (tmp==BUSINESS_NUMBER)
            strcat(result,"business");
        else if (tmp==WORLD_NUMBER)
            strcat (result,"world");
        else if (tmp==SCITECH_NUMBER)
            strcat (result,"sci_tech");
        else if (tmp==HEALTH_NUMBER)
            strcat (result,"health");
        else if (tmp==ENTERTAINMENT_NUMBER)
            strcat (result,"entertainment");
        else if (tmp==US_NUMBER)
            strcat (result,"us");
        else
            strcat (result,"sport");

        strcat (result,doubleQuote);

        strcat(result,closed_bracket);strcat(result,nextLine);strcat(result,closed_brace);

        //decode_html_entities_utf8(dest,result);

        //printf ("%s\n\n",result);

        CURL *curl = curl_easy_init();
        struct curl_slist *list = NULL;
        if(curl)
        {
            list = curl_slist_append(list,"X-Requested-With: XMLHttpRequest");
            list = curl_slist_append(list, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_URL, "http://team17:95105573_95105681@www.fop-project.ir/news");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(result));
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, result);
            curl_easy_perform(curl);
        }
    }
    fclose (data);
}
