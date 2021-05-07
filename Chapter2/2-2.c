//Exercise 2-2.
//Write a loop equivalent to the for loop above without using && or ||

for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
  s[i] = c;


//Rewritten

for (i=0; i<lim-1; ++i) {
  if ((c = getchar()) != '\n')
    break;
  if (c != EOF)
    break;
  s[i] = c;
 }

