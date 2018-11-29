// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <charon/base>
#include <curl/curl.h>
#include <cstdlib>
#include <cstring>
#include <charon/base>
#include <iostream>

using charon::string;
using namespace charon::net;

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  HttpClient * client = (HttpClient *)userp;

  client->m_data = (char *) realloc(client->m_data, client->m_size + realsize + 1);
  if(client->m_data == NULL) {
    // out of memory!
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(client->m_data[client->m_size]), contents, realsize);
  client->m_size += realsize;
  client->m_data[client->m_size] = 0;

  return realsize;
}

HttpClient::HttpClient(const char * url)
{
  size_t size;
  size = strlen(url);
  m_url = new char[size + 1];
  strcpy(m_url, url);
  m_url[size] = '\0';

  m_body = new char[1]();

  m_data = new char[1]();  // will be grown as needed by the realloc above
  m_size = 0;                   // no data at this point
  m_list = NULL;

  //curl_global_init(CURL_GLOBAL_ALL);

  // init the curl session
  m_curl = curl_easy_init();

  // url
  curl_easy_setopt(m_curl, CURLOPT_URL, url);

  // example.com is redirected, so we tell libcurl to follow redirection
  curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);

  // send all data to this function
  curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  // we pass our 'chunk' struct to the callback function
  curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)this);

  // headers
  curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);

  // some servers don't like requests that are made without a user-agent field, so we provide one
  curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
}

HttpClient::~HttpClient()
{
  // cleanup curl stuff
  curl_easy_cleanup(m_curl);


  // we're done with libcurl, so clean it up
  curl_global_cleanup();

  // free memory
  delete[] m_data;
  delete[] m_url;
  delete[] m_body;
}

void HttpClient::appendHeader(const char * header)
{
   m_list = curl_slist_append(m_list, header);
}

void HttpClient::setVerbose(bool verbose)
{
  if( verbose ) {
    curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
  } else {
    curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 0L);
  }
}

void HttpClient::setBody(const char * body)
{
  size_t size;
  size = strlen(body);
  m_body = new char[size + 1];
  strcpy(m_body, body);
  m_body[size] = '\0';
}

const char * HttpClient::body()
{
  return m_body;
}

char * HttpClient::performGet()
{
  CURLcode res;

  /* set our custom set of headers */
  res = curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_list);

  // get it!
  res = curl_easy_perform(m_curl);

  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  return perform();
}

char * HttpClient::performPost()
{
  CURLcode res;

  /* set our custom set of headers */
  res = curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_list);

  /* POST */
  curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(m_curl, CURLOPT_POST, 1);
  curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, m_body);
  curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, strlen(m_body));

  // post it!
  res = curl_easy_perform(m_curl);

  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  return perform();
}

char * HttpClient::performPut()
{
  CURLcode res;

  /* set our custom set of headers */
  res = curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_list);

  /* PUT */
  curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_easy_setopt(m_curl, CURLOPT_POST, 1);
  curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, m_body);
  curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, strlen(m_body));

  // put it!
  res = curl_easy_perform(m_curl);

  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  return new char[1]();
}

char * HttpClient::performDelete()
{
  CURLcode res;

  /* set our custom set of headers */
  res = curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_list);

  /* DELETE */
  curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "DELETE");

  // delete it!
  res = curl_easy_perform(m_curl);

  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  return perform();
}

int HttpClient::status()
{
  return m_status;
}

char * HttpClient::data()
{
  return m_data;
}

char * HttpClient::perform()
{
  char * body;
  int    index;

  if( m_size ) {

    // parse status
    index = string::indexOf(m_data, " ");
    if( index > -1 ) {
      m_status = atoi(string::mid(m_data, index + 1, index + 4));
    } else {
      m_status = 0;
    }

    //parse body
    index = string::indexOf(m_data, "\r\n\r\n");
    if( index > 0 ) {
      body = string::mid(m_data, index+4, -1);
    } else {
      body = new char[1]();
    }
  } else {
    m_status = 0;
    body = new char[1]();
  }

  return body;
}
