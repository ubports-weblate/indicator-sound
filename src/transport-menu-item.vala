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

using Dbusmenu;
using Gee;
using DbusmenuTransport;

public class TransportMenuitem : PlayerItem
{
  public enum action{
    PREVIOUS,
    PLAY_PAUSE,
    NEXT
  }

  public enum state{
    PLAYING,
    PAUSED
  }
  
  public TransportMenuitem(PlayerController parent)
  {
    Object(item_type: MENUITEM_TYPE, owner: parent); 
    this.property_set_int(MENUITEM_PLAY_STATE, 1);    
  }

  public void change_play_state(state update)
  {
    debug("UPDATING THE TRANSPORT DBUSMENUITEM PLAY STATE WITH VALUE %i",
          (int)update);
    this.property_set_int(MENUITEM_PLAY_STATE, update); 
  }
  
  public override void handle_event(string name, GLib.Value input_value, uint timestamp)
  {
    int input = input_value.get_int();
    debug("handle_event with value %s", input.to_string());
    debug("transport owner name = %s", this.owner.app_info.get_name());
    this.owner.mpris_bridge.transport_update((action)input);
  } 

  public static HashSet<string> attributes_format()
  {
    HashSet<string> attrs = new HashSet<string>();    
    attrs.add(MENUITEM_PLAY_STATE);
    return attrs;
  } 

}