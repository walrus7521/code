/*
 *
 *  Fetches and dumps a website:
 *      build using: gcc -lcurl getweb.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

struct MemoryStruct {
      char *memory;
      size_t size;
};


void hexdump(char *buffer, unsigned int length)
{
    char OffsetBuf[10];
    unsigned int LastStart = 0, i, k, j;
    for (i = 0 ; i < length ; i++) {
        if (i % 16 == 0) {
            sprintf(OffsetBuf, "%03x", i);
            printf("%4s:", OffsetBuf);
        }
        if (i % 4 == 0) {
            printf(" ");
        }
        printf("%02x ", buffer[i]);
        if (i % 16 == 15 || i == length-1) {
            if (i == length-1) {
                for (k = i % 16 ; k < 15 ; k++) {
                     printf( "   " );
                     if (k % 4 == 3 && k % 16 != 0) {
                         printf(" ");
                     }
                }
            }
            printf("|");
            for (j = LastStart ; j <= i ; j++) {
                if (j % 4 == 0) {
                    printf(" ");
                }
                if (buffer[j] > 31 && buffer[j] < 127) {
                    printf("%c", buffer[j]);
                } else {
                    printf(".");
                }
            }
            if (i == length-1) {
                printf("\n");
                break;
            }
            printf("\n");
            LastStart += 16;
        }        
    }
}


static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
      size_t realsize = size * nmemb;
      struct MemoryStruct *mem = (struct MemoryStruct *)userp;

      printf("yo sup...\n");
      mem->memory = realloc(mem->memory, mem->size + realsize + 1);
      if (mem->memory == NULL) {
        /* out of memory! */ 
        printf("not enough memory (realloc returned NULL)\n");
        exit(EXIT_FAILURE);
      }

      memcpy(&(mem->memory[mem->size]), contents, realsize);
      mem->size += realsize;
      mem->memory[mem->size] = 0;

      hexdump(mem->memory, realsize);
      return realsize;
}


int main(void)
{
      CURL *curl_handle;

      struct MemoryStruct chunk;

      chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
      chunk.size = 0;    /* no data at this point */ 

      curl_global_init(CURL_GLOBAL_ALL);

      /* init the curl session */ 
      curl_handle = curl_easy_init();

      /* specify URL to get */ 
      curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.aromahead.com/");

      /* send all data to this function  */ 
      curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

      /* we pass our 'chunk' struct to the callback function */ 
      curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

      /* some servers don't like requests that are made without a user-agent
         field, so we provide one */ 
      curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

      /* get it! */ 
      curl_easy_perform(curl_handle);

      /* cleanup curl stuff */ 
      curl_easy_cleanup(curl_handle);

      /*
       * Now, our chunk.memory points to a memory block that is chunk.size
       * bytes big and contains the remote file.
       *
       * Do something nice with it!
       *
       * You should be aware of the fact that at this point we might have an
       * allocated data block, and nothing has yet deallocated that data. So when
       * you're done with it, you should free() it as a nice application.
       */ 

      printf("%lu bytes retrieved\n", (long)chunk.size);

      if(chunk.memory)
        free(chunk.memory);

      /* we're done with libcurl, so clean it up */ 
      curl_global_cleanup();

      return 0;
}

