#include <oberon/classes/OHttpClient.h>
#include <curl/curl.h>
#include <cstdlib>
#include <cstring>

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    // out of memory!
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

OHttpClient::OHttpClient(const char * url)
{
  m_url = url;
  m_chunk.memory = (char *) malloc(1);  // will be grown as needed by the realloc above
  m_chunk.size = 0;    // no data at this point
  m_chunk_list = NULL;

  curl_global_init(CURL_GLOBAL_ALL);

  // init the curl session
  m_curl = curl_easy_init();

  // url
  curl_easy_setopt(m_curl, CURLOPT_URL, url);
}

OHttpClient::~OHttpClient()
{
  // cleanup curl stuff
  curl_easy_cleanup(m_curl);

  // free memory result
  free(m_chunk.memory);

  // we're done with libcurl, so clean it up
  curl_global_cleanup();
}

void OHttpClient::appendHeader(const char * header)
{
   m_chunk_list = curl_slist_append(m_chunk_list, header);
}

void OHttpClient::setVerbose(bool verbose)
{
  m_verbose = verbose;
  curl_easy_setopt(m_curl, CURLOPT_VERBOSE, verbose);//1L);
}

bool OHttpClient::verbose()
{
  return m_verbose;
}

void OHttpClient::setBody(const char * body)
{
   m_body = body;
}

const char * OHttpClient::body()
{
  return m_body;
}

char * OHttpClient::performGet()
{
  CURLcode res;

  /* set our custom set of headers */
  res = curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_chunk_list);

  // send all data to this function
  curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  // we pass our 'chunk' struct to the callback function
  curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)& m_chunk);

  // some servers don't like requests that are made without a user-agent field, so we provide one
  curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  // get it!
  res = curl_easy_perform(m_curl);

  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  m_chunk.memory[m_chunk.size] = '\0';
  return m_chunk.memory;
}

char * OHttpClient::performPost()
{
  CURLcode res;

  /* set our custom set of headers */
  res = curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_chunk_list);

  /* POST */
  curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(m_curl, CURLOPT_POST, 1);
  curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, m_body);
  curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, strlen(m_body));

  // send all data to this function
  curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  // we pass our 'chunk' struct to the callback function
  curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)& m_chunk);

  // some servers don't like requests that are made without a user-agent field, so we provide one
  curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  // post it!
  res = curl_easy_perform(m_curl);

  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  m_chunk.memory[m_chunk.size] = '\0';

  return m_chunk.memory;
}

char * OHttpClient::performPut()
{
  CURLcode res;

  /* set our custom set of headers */
  res = curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_chunk_list);

  /* PUT */
  curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_easy_setopt(m_curl, CURLOPT_POST, 1);
  curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, m_body);
  curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, strlen(m_body));

  // send all data to this function
  curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  // we pass our 'chunk' struct to the callback function
  curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)& m_chunk);

  // some servers don't like requests that are made without a user-agent field, so we provide one
  curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  // put it!
  res = curl_easy_perform(m_curl);

  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  m_chunk.memory[m_chunk.size] = '\0';

  return m_chunk.memory;
}

char * OHttpClient::performDelete()
{
  CURLcode res;

  /* set our custom set of headers */
  res = curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_chunk_list);

  /* DELETE */
  curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "DELETE");

  // send all data to this function
  curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  // we pass our 'chunk' struct to the callback function
  curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)& m_chunk);

  // some servers don't like requests that are made without a user-agent field, so we provide one
  curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  // delete it!
  res = curl_easy_perform(m_curl);

  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  m_chunk.memory[m_chunk.size] = '\0';

  return m_chunk.memory;
}