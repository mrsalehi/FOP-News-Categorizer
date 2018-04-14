# FOP-News-Categorizer

A news classifier code based on ideas from the statistical learning in C. This code was trained
on a set of classified news acquired from the curl library.

The program first gets the categorized news (training data) from the web and then extracts the content and category of each news. Then it finds a set of effective words in the training data with which the category of an uncategorized news can be determined(for example the word "stock" appears many times in economic news. So if this word exists in an uncategorized news then probably the news belongs to "Economic" category). In order to get a better performance, effective words are stored in a trie. After that, the program gets the uncategorized news and it should specify the category to which each news belongs. The program searches for the effective words in the news and make a vector from the number of appearances of each effective word in the news and do the same for each category. Then by cross producting the vectors of news and categories it 


