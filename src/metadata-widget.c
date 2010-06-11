/*
Copyright 2010 Canonical Ltd.

Authors:
    Conor Curran <conor.curran@canonical.com>

This program is free software: you can redistribute it and/or modify it 
under the terms of the GNU General Public License version 3, as published 
by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranties of 
MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR 
PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along 
with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib/gi18n.h>
#include "metadata-widget.h"
#include "common-defs.h"
#include <gtk/gtk.h>

// TODO: think about leakage: ted !



static DbusmenuMenuitem* twin_item;

typedef struct _MetadataWidgetPrivate MetadataWidgetPrivate;

struct _MetadataWidgetPrivate
{
	GtkWidget* hbox;
};

#define METADATA_WIDGET_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), METADATA_WIDGET_TYPE, MetadataWidgetPrivate))

/* Prototypes */
static void metadata_widget_class_init (MetadataWidgetClass *klass);
static void metadata_widget_init       (MetadataWidget *self);
static void metadata_widget_dispose    (GObject *object);
static void metadata_widget_finalize   (GObject *object);
// keyevent consumers
static gboolean metadata_widget_button_press_event (GtkWidget *menuitem, 
                                  									GdkEventButton *event);
static gboolean metadata_widget_button_release_event (GtkWidget *menuitem, 
                                  										GdkEventButton *event);


// Dbusmenuitem update callback
static void metadata_widget_update_state(gchar * property, 
                                       GValue * value,
                                       gpointer userdata);



G_DEFINE_TYPE (MetadataWidget, metadata_widget, GTK_TYPE_MENU_ITEM);



static void
metadata_widget_class_init (MetadataWidgetClass *klass)
{
	GObjectClass 			*gobject_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass    *widget_class = GTK_WIDGET_CLASS (klass);

	widget_class->button_press_event = metadata_widget_button_press_event;
  widget_class->button_release_event = metadata_widget_button_release_event;
	
	g_type_class_add_private (klass, sizeof (MetadataWidgetPrivate));

	gobject_class->dispose = metadata_widget_dispose;
	gobject_class->finalize = metadata_widget_finalize;

}

static void
metadata_widget_init (MetadataWidget *self)
{
	g_debug("MetadataWidget::metadata_widget_init");

	MetadataWidgetPrivate * priv = METADATA_WIDGET_GET_PRIVATE(self);
	GtkWidget *hbox;

	hbox = gtk_hbox_new(TRUE, 2);

	g_signal_connect(G_OBJECT(twin_item), "property-changed", G_CALLBACK(metadata_widget_update_state), self);

  gtk_widget_show_all (priv->hbox);
  gtk_container_add (GTK_CONTAINER (self), hbox);
	
}

static void
metadata_widget_dispose (GObject *object)
{
	//if(IS_METADATA_WIDGET(object) == TRUE){ 
	//	MetadataWidget * priv = METADATA_WIDGET_GET_PRIVATE(METADATA_WIDGET(object));
	//	g_object_unref(priv->previous_button);
	//}
	G_OBJECT_CLASS (metadata_widget_parent_class)->dispose (object);
}

static void
metadata_widget_finalize (GObject *object)
{
	G_OBJECT_CLASS (metadata_widget_parent_class)->finalize (object);
}

/* Suppress/consume keyevents */
static gboolean
metadata_widget_button_press_event (GtkWidget *menuitem, 
                                  GdkEventButton *event)
{
	g_debug("MetadataWidget::menu_press_event");
	return TRUE;
}

static gboolean
metadata_widget_button_release_event (GtkWidget *menuitem, 
                                  GdkEventButton *event)
{
	g_debug("MetadataWidget::menu_release_event");
	return TRUE;
}


//TODO figure out why the userdata is not what I expect it to be. 
static void metadata_widget_update_state(gchar *property, GValue *value, gpointer userdata)
{
	//MetadataWidget* bar = (MetadataWidget*)userdata;
	// TODO problem line	
	//if(IS_METADATA_WIDGET(bar)){
	//g_debug("after line 1!!");

	//MetadataWidget *priv = METADATA_WIDGET_GET_PRIVATE(bar);
	//g_debug("after line 2!!");
	//gchar* label = "changed";
	//g_debug("after line 3!!");
	//gtk_button_set_label(GTK_BUTTON(priv->play_button), g_strdup(label));
	//}
	//if(GTK_IS_BUTTON(GTK_BUTTON(priv->play_button))){
	
	//	gtk_button_set_label(GTK_BUTTON(priv->play_button), g_strdup(label));
	//	g_debug("its a button");
	//}
	//else{
		//g_debug("No Goddamn button!!");
	//}
	//}
	g_debug("metadata_widget_update_state - with property  %s", property);  

	if (value == NULL){
		g_debug("value is null");
		return;
	}
	// TODO problem line	
	//gchar* input = g_strdup(g_value_get_string(value));
	//g_debug("metadata_widget_update_state - with value  %s", input);  

}

 /**
 * transport_new:
 * @returns: a new #MetadataWidget.
 **/
GtkWidget* 
metadata_widget_new(DbusmenuMenuitem *item)
{
	twin_item = item;
	return g_object_new(METADATA_WIDGET_TYPE, NULL);
}

