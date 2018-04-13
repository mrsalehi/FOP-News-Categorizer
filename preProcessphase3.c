int preProcess(news **Category_Root,news **News_Root,int *Category_Number)
{
    int *occurrence=calloc (7 , sizeof (int));

    process(occurrence,Category_Root,News_Root,Category_Number);

    char *buffer=malloc (20 * sizeof (char));

    int i;

    for (i=0;i<7;i++)
        iterateTrie(Category_Root,Category_Root[i],occurrence,buffer,0,i);

    qsort(word, indicatorToWord, sizeof(words), cmp);

//    for (i=0;i<FINAL_NUMBER;i++)
//            printf ("%s\n",word[i].name);

    return 0;
}
///----------------------------------------------------------------------------------------
news *getNode()
{
    news *pNode = NULL;
    pNode = (news*) malloc(sizeof(news));
    if (pNode)
    {
        int i;
        pNode->isLeaf = false;
        pNode->occurrence=0;
        for (i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}
///--------------------------------------------------------------------------
void insert(news *root,char *key)
{
    int level;
    int length = strlen(key);
    int index;
    news *pCrawl = root;
    for (level = 0; level < length; level++)
    {
        index = ((int)key[level]-(int)'a');
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isLeaf = true;
    pCrawl->occurrence++;
}
///--------------------------------------------------------------------------
int search(news *root,char *key)
{
    int level;
    int length = (int) strlen(key);
    int index;
    news *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = ((int)key[level]-(int)'a');
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    if (pCrawl != NULL && pCrawl->isLeaf)
        return pCrawl->occurrence;
    else
        return 0;
}
///--------------------------------------------------------------------------
int iterateTrie(news **Category_Root,news *root,int *occurrence,char *buffer,int k,int num)
{
    int i;

    if (root == NULL)
        return;

    if (root->isLeaf==true)
    {
        double temp = 0.0 ;
        int *occurInCategory = calloc (7 , sizeof (int));

        if ((double) root->occurrence/occurrence[num] >0.0003)
        {
            for (i=0;i<7;i++)
            {
                occurInCategory[i]=search(Category_Root[i],buffer);

                if (i!=num)
                    temp -= (double) 1000 * occurInCategory[i]/occurrence[i];
                else
                    temp += (double) 2000 * occurInCategory[i]/occurrence[i];
            }
        }

        word[indicatorToWord].val = temp;
        strcpy(word[indicatorToWord].name, buffer);
        word[indicatorToWord].cat=num;

        for (i=0;i<7;i++)
            word[indicatorToWord].occurrence+=occurInCategory[i];

        indicatorToWord++;
    }

    buffer[k + 1] = '\0';

    for (i = 0; i < 26; i++)
    {
        buffer[k] = (char)((int)'a' + i);
        if (root->children[i]!=NULL)
            iterateTrie(Category_Root,root->children[i],occurrence,buffer,k + 1,num);
    }
    buffer[k] = '\0';
}
///--------------------------------------------------------------------------
void splitFunc(news *root,news *news_root,char *description,char *title)
{
    int index,Words_Number=0;
    int indicator=0;
    int Result_Length=0;
    bool flag=false;

    char *result = malloc (500 * sizeof (char));
    char **p = malloc (100 * sizeof (char*));

    int i=0;

    for (i=0;i<100;i++)
        p[i]=malloc (30 * sizeof (char));

    while (indicator<strlen(description))
    {
         if (description[indicator]==' ')
        {
            index=(int)result[0];
            if (index>=97 && index<=122)
                insert(news_root,result);

            for (i=0;i<Words_Number;i++)
            {
                if (strcmp( result , p[i]) == 0)
                {
                    flag=true;
                    break;
                }
            }
            if (flag==false)
            {
                strcpy(p[Words_Number],result);
                Words_Number++;
                index=(int)result[0];
                if (index>=97 && index<=122)
                    insert (root,result);
            }

            Result_Length=0;
            result[0]='\0';
            flag=false;
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
    flag=false;

    while (indicator<strlen(title))
    {
        if (title[indicator]==' ')
       {
            insert (news_root,result);

            for (i=0;i<Words_Number;i++)
            {
                if (strcmp( result, p[i])==0)
                    {
                        flag=true;
                        break;
                    }
            }

            if (flag==false)
            {
                strcpy(p[Words_Number],result);
                Words_Number++;
                index=(int)result[0];
                if (index>=97 && index<=122)
                    insert (root,result);
            }
            Result_Length=0;
            result[0]='\0';
            flag=false;
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
///--------------------------------------------------------------------------
int cmp(const void *a, const void *b)
{
    words *A = (words *) a;
    words *B = (words *) b;
    if(A->val > B->val)
        return -1;
    else
        return 1;
}
///----------------------------------------------------------------------------------------
