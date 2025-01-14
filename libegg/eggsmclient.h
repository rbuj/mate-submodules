/* eggsmclient.h
 * Copyright (C) 2007 Novell, Inc.
 * Copyright (C) 2012-2021 MATE Developers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __EGG_SM_CLIENT_H__
#define __EGG_SM_CLIENT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define EGG_TYPE_SM_CLIENT (egg_sm_client_get_type())
G_DECLARE_DERIVABLE_TYPE(EggSMClient, egg_sm_client, EGG, SM_CLIENT, GObject)

typedef enum {
  EGG_SM_CLIENT_END_SESSION_DEFAULT,
  EGG_SM_CLIENT_LOGOUT,
  EGG_SM_CLIENT_REBOOT,
  EGG_SM_CLIENT_SHUTDOWN
} EggSMClientEndStyle;

typedef enum {
  EGG_SM_CLIENT_MODE_DISABLED,
  EGG_SM_CLIENT_MODE_NO_RESTART,
  EGG_SM_CLIENT_MODE_NORMAL
} EggSMClientMode;

struct _EggSMClientClass {
  GObjectClass parent_class;

  /* signals */
  void (*save_state)(EggSMClient *client, GKeyFile *state_file);

  void (*quit_requested)(EggSMClient *client);
  void (*quit_cancelled)(EggSMClient *client);
  void (*quit)(EggSMClient *client);

  /* virtual methods */
  void (*startup)(EggSMClient *client, const char *client_id);
  void (*set_restart_command)(EggSMClient *client, int argc, const char **argv);
  void (*set_discard_command)(EggSMClient *client, int argc, const char **argv);
  void (*will_quit)(EggSMClient *client, gboolean will_quit);
  gboolean (*end_session)(EggSMClient *client, EggSMClientEndStyle style,
                          gboolean request_confirmation);

  /* Padding for future expansion */
  void (*_egg_reserved1)(void);
  void (*_egg_reserved2)(void);
  void (*_egg_reserved3)(void);
  void (*_egg_reserved4)(void);
};

GOptionGroup *egg_sm_client_get_option_group(void);

/* Initialization */
void egg_sm_client_set_mode(EggSMClientMode mode);
EggSMClientMode egg_sm_client_get_mode(void);
EggSMClient *egg_sm_client_get(void);

/* Resuming a saved session */
gboolean egg_sm_client_is_resumed(const EggSMClient *client);
GKeyFile *egg_sm_client_get_state_file(EggSMClient *client);

/* Alternate means of saving state */
void egg_sm_client_set_restart_command(EggSMClient *client, int argc,
                                       const char **argv);
void egg_sm_client_set_discard_command(EggSMClient *client, int argc,
                                       const char **argv);

/* Handling "quit_requested" signal */
void egg_sm_client_will_quit(EggSMClient *client, gboolean will_quit);

/* Initiate a logout/reboot/shutdown */
gboolean egg_sm_client_end_session(EggSMClientEndStyle style,
                                   gboolean request_confirmation);

G_END_DECLS

#endif /* __EGG_SM_CLIENT_H__ */
