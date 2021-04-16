/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2021 Azael Reyes <azael.devel@gmail.com>
 * 
 * nanoHttp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * nanoHttp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include "http.hh"

static int
answer_to_connection (void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls)
{
  char *user;
  char *pass;
  int fail;
  int ret;
  struct MHD_Response *response;
  (void)cls;               /* Unused. Silent compiler warning. */
  (void)url;               /* Unused. Silent compiler warning. */
  (void)version;           /* Unused. Silent compiler warning. */
  (void)upload_data;       /* Unused. Silent compiler warning. */
  (void)upload_data_size;  /* Unused. Silent compiler warning. */

  if (0 != strcmp (method, "GET"))
    return MHD_NO;
  if (NULL == *con_cls)
    {
      *con_cls = connection;
      return MHD_YES;
    }
  pass = NULL;
  user = MHD_basic_auth_get_username_password (connection,
                                               &pass);
  fail = ( (NULL == user) ||
	   (0 != strcmp (user, "root")) ||
	   (0 != strcmp (pass, "pa$$w0rd") ) );
  if (NULL != user) MHD_free (user);
  if (NULL != pass) MHD_free (pass);
  if (fail)
    {
      const char *page = "<html><body>Go away.</body></html>";
      response =
	MHD_create_response_from_buffer (strlen (page), (void *) page,
					 MHD_RESPMEM_PERSISTENT);
      ret = MHD_queue_basic_auth_fail_response (connection,
						"my realm",
						response);
    }
  else
    {
      const char *page = "<html><body>A secret.</body></html>";
      response =
	MHD_create_response_from_buffer (strlen (page), (void *) page,
					 MHD_RESPMEM_PERSISTENT);
      ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    }
  MHD_destroy_response (response);
  return ret;
}


int
main (void)
{
  struct MHD_Daemon *daemon;

  daemon = MHD_start_daemon (MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                             &answer_to_connection, NULL, MHD_OPTION_END);
  if (NULL == daemon)
    return 1;

  (void) getchar ();

  MHD_stop_daemon (daemon);
  return 0;
}