#include <stdio.h>
#include <string.h>

const int MAXSIZE = 10005;
void Add(char *str1, char *str2, char *str3);
void Minus(char *str1, char *str2, char *str3);
void Mul(char *str1, char *str2, char *str3);
void Div(char *str1, char *str2, char *str3);

int main()
{
    char *s1 = "68932147586";
    char *s2 = "468711654886";
    char s3[MAXSIZE];

    Add(s1, s2, s3);
    printf("%s\n", s3);

    memset(s3, '0', sizeof(s3));
    Minus(s2, s1, s3);
    printf("%s\n", s3);

    memset(s3, '0', sizeof(s3));
    Mul(s1, s2, s3);
    printf("%s\n", s3);

    memset(s3, '0', sizeof(s3));
    Div(s1, s2, s3);
    printf("%s\n", s3);

    return 0;
}

void Add(char *str1, char *str2, char *str3)
{
    // str3 = str1 + str2;
    int i, j, i1, i2, tmp, carry;
    int len1 = strlen(str1), len2 = strlen(str2);
    char ch;
    i1 = len1-1;
    i2 = len2-1;
    j = carry = 0;
    for( ; i1 >= 0 && i2 >= 0; ++j, --i1, --i2 ){
        tmp = str1[i1]-'0'+str2[i2]-'0'+carry;
        carry = tmp/10;
        str3[j] = tmp%10+'0';
    }
    while( i1 >= 0 ){
        tmp = str1[i1--]-'0'+carry;
        carry = tmp/10;
        str3[j++] = tmp%10+'0';
    }
    while( i2 >= 0 ){
        tmp = str2[i2--]-'0'+carry;
        carry = tmp/10;
        str3[j++] = tmp%10+'0';
    }
    if( carry )
        str3[j++] = carry+'0';
    str3[j] = '\0';
    for( i=0, --j; i < j; ++i, --j ){
        ch = str3[i];
        str3[i] = str3[j];
        str3[j] = ch;
    }
}

void Minus(char *str1, char *str2, char *str3)
{
    // str3 = str1-str2 (str1 > str2)
    int i, j, i1, i2, tmp, carry;
    int len1 = strlen(str1), len2 = strlen(str2);
    char ch;
    i1 = len1-1;
    i2 = len2-1;
    j = carry = 0;
    while( i2 >= 0 ){
        tmp = str1[i1]-str2[i2]-carry;
        if( tmp < 0 ) {
            str3[j] = tmp+10+'0';
            carry = 1;
        }
        else {
            str3[j] = tmp+'0';
            carry = 0;
        }
        --i1;
        --i2;
        ++j;
    }
    while( i1 >= 0 ){
        tmp = str1[i1]-'0'-carry;
        if( tmp < 0 ) {
            str3[j] = tmp+10+'0';
            carry = 1;
        }
        else{
            str3[j] = tmp+'0';
            carry = 0;
        }
        --i1;
        ++j;
    }
    --j;
    while( str3[j] == '0' && j > 0 )
        --j;
    str3[++j] = '\0';
    for( i=0, --j; i < j; ++i, --j ){
        ch = str3[i];
        str3[i] = str3[j];
        str3[j] = ch;
    }
}

void Mul(char *str1, char *str2, char *str3)
{
    int i, j, i1, i2, tmp, carry, jj;
    int len1 = strlen(str1), len2 = strlen(str2);
    char ch;
    jj = carry = 0;
    for( i1=len1-1; i1 >= 0; --i1 ){
        j = jj;
        for( i2=len2-1; i2 >= 0; --i2, ++j ){
            tmp = (str3[j]-'0')+(str1[i1]-'0')*(str2[i2]-'0')+carry;
            if( tmp > 9 ){
                carry = tmp/10;
                str3[j] = tmp%10+'0';
            }
            else {
                str3[j] = tmp+'0';
                carry = 0;
            }
        }
        if( carry ) {
            str3[j] = carry+'0';
            carry = 0; ++j;
        }
        ++jj;
    }
    --j;
    while( str3[j] == '0' && j > 0 )
        --j;
    str3[++j] = '\0';
    for( i=0, --j; i < j; ++i, --j ){
        ch = str3[i];
        str3[i] = str3[j];
        str3[j] = ch;
    }
}

void Div(char *str1, char *str2, char *str3)
{
    int i1, i2, i, j, jj, tag, carry, cf, c[MAXSIZE];
    int len1 = strlen(str1), len2 = strlen(str2), lend;
    char d[MAXSIZE];
    memset(c, 0, sizeof(c));
    memcpy(d, str1, len2);
    lend = len2;
    j = 0;
    for( i1=len2-1; i1 < len1; ++i1 ){
        if( lend < len2 ){
            d[lend] = str1[i1+1];
            c[j] = 0;
            ++j;
            ++lend;
        }
        else if( lend == len2 ){
            jj = 1;
            for( i=0; i < lend; ++i ){
                if( d[i] > str2[i] )
                    break;
                else if( d[i] < str2[i] ){
                    jj = 0;
                    break;
                }
            }
            if( jj == 0 ){
                d[lend] = str1[i1+1];
                c[j] = 0;
                ++j;
                ++lend;
                continue;
            }
        }
        if( jj==1 || lend > len2 ){
            cf = jj=0;
            while( d[jj] <= '0' && jj < lend )
                ++jj;
            if( lend-jj > len2 )
                cf = 1;
            else if( lend-jj < len2 )
                cf = 0;
            else{
                i2 = 0;
                cf = 1;
                for( i=jj; i < lend; ++i ){
                    if( d[i] < str2[i2] ){
                        cf = 0;
                        break;
                    }
                    else if( d[i] > str2[i2] ){
                        break;
                    }
                    ++i2;
                }
            }//else
            while( cf ){
                i2 = len2-1;
                cf = 0;
                for( i=lend-1; i >= lend-len2; --i ){
                    d[i] = d[i]-str2[i2]+'0';
                    if( d[i] < '0' ){
                        d[i] = d[i]+10;
                        carry = 1;
                        --d[i-1];
                    }
                    else
                        carry = 0;
                    --i2;
                }
                ++c[j];
                jj=0;
                while( d[jj] <= '0' && jj < lend )
                    ++jj;
                if( lend-jj > len2 )
                    cf = 1;
                else if( lend-jj < len2 )
                    cf = 0;
                else{
                    i2 = 0;
                    cf = 1;
                    for( i=jj; i < lend; ++i ){
                        if( d[i] < str2[i2] ){
                            cf = 0; break;
                        }
                        else if( d[i] > str2[i2] ){
                            break;
                        }
                        ++i2;
                    }
                }//else
            }//while

            jj = 0;
            while( d[jj] <= '0' && jj < lend )
                ++jj;
            for( i=0;i < lend-jj; ++i )
                d[i] = d[i+jj];
            d[i] = str1[i1+1];
            lend = i+1;
            ++j;
        }//else
    }//for
    i = tag = 0;
    while( c[i] == 0 )
        ++i;
    for( ; i < j; ++i, ++tag )
        str3[tag] = c[i]+'0';
    str3[tag] = '\0';
}
