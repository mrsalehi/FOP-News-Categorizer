#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

///-----------------------------------------------------------------------------------
int main()
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

    FILE *f=fopen ("categories.txt","r");

    char *n= malloc(20 *sizeof (char));

    int i;

    while(fscanf (f,"%s",n)==1)
    {
        result[0]='\0';

        fgets(Tmp_String,3000,data);

        strcat(result,open_brace);strcat(result,nextLine);

        strcat(result,title);strcat(result,doubleQuote);strcat(result,Tmp_String);

        fgets(Tmp_String,3000,data);

        strcat(result,date);strcat(result,doubleQuote);strcat(result,Tmp_String);

        fgets(Tmp_String,3000,data);

        strcat(result,description);strcat(result,doubleQuote);strcat(result,Tmp_String);

        strcat(result,categorized);

        strcat(result,comma);strcat(result,nextLine);

        strcat(result,category);strcat(result,open_bracket);strcat (result,doubleQuote);

        strcat (result,n);

        strcat (result,doubleQuote);

        strcat(result,closed_bracket);strcat(result,nextLine);strcat(result,closed_brace);

        //decode_html_entities_utf8(dest,result);


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
    fclose (f);
}
