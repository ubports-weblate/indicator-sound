/*
This service primarily controls PulseAudio and is driven by the sound indicator menu on the panel.
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

public class PlayerItem : Dbusmenu.Menuitem
{
	public MprisController mpris_adaptor;
	
	public PlayerItem()
	{		
	}

	public void update(HashTable<string, Value?> data, HashSet<string> attributes)
	{
		debug("PlayerItem::update()");
		foreach(string property in attributes){
			string[] input_keys = property.split("-");
			string search_key = input_keys[input_keys.length-1 : input_keys.length][0];
			if (data.lookup(search_key).holds (typeof (string))){
				this.property_set(property, this.sanitize_string(data.lookup(search_key) as string));
			}			    
			else if (data.lookup(search_key).holds (typeof (int))){
				// Circumvent weird vala bug
				int* v = (int*)data.lookup(search_key);
				int r = *v;
				this.property_set_int(property, r);
			}
			else if(data.lookup(search_key).holds (typeof (bool))){
				bool* b = (bool*)data.lookup(search_key);
				bool input = *b;
				this.property_set_bool(property, input);
			}
		}
	}	

	public void set_adaptor(MprisController adaptor)
	{
		this.mpris_adaptor = adaptor;		
	}


	public static string sanitize_string(string st)
	{
		string result = st.strip();
		if(result.has_prefix("file:///")){
			result = result.slice(7, result.len());		                   
		}
		debug("Sanitize string - result = %s", result);
		return result;
	}

	
	//----- Custom constructors for player items ----------------//
	// Title item
	public static PlayerItem new_title_item(dynamic string name)
	{
		PlayerItem item = new PlayerItem();
		item.property_set(MENUITEM_PROP_LABEL, name);					
		item.property_set(MENUITEM_PROP_ICON_NAME, "applications-multimedia");			
		return item;		
	}

	// Separator item
	public static PlayerItem new_separator_item()
	{
		PlayerItem separator = new PlayerItem();
		separator.property_set(MENUITEM_PROP_TYPE, CLIENT_TYPES_SEPARATOR);					
		return separator;
	}	
}

