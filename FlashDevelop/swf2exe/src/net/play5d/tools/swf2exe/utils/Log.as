/**
 * Copyright (C) 2021, 5DPLAY Game Studio
 * All rights reserved.
 * 
 * This software is distributed under the MIT license.
 * Any person or organization may use this library free of charge, 
 * but it must follow the following points :
 * 
 * 1. No person or organization may claim to 
 *    have written the original source code.
 * 
 * 2. In any case, the author is not liable for 
 *    any consequences caused by the use of part 
 *    of the code of this software.
 * 
 * 3. This section shall not be deleted or altered 
 *    from any source.
 * 
 */

package net.play5d.tools.swf2exe.utils {
	
	import flash.text.TextField;
	
	/**
	 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
	 * @version	1.0
	 * @since	4/27/2021 4:59 PM
	 */
	public class Log {
		
		private static var _txt:TextField;
		
		/**
		 * Constructor.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:29 PM
		 * 
		 * @return	void
		 */
		public function Log():void {}
		
		/**
		 * Initlize.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:29 PM
		 * 
		 * @param	txt	TextField, <b>required</b>.
		 * 
		 * @return	void
		 */
		public static function init(txt:TextField):void {
			_txt = txt;
		}
		
		/**
		 * Log.
		 * 
		 * @param	v	String, <b>required</b>.
		 * 
		 * @return	void
		 */
		public static function log(v:String):void {
			trace(v);
			_txt.appendText(v + "\n");
			_txt.scrollV = _txt.maxScrollV;
		}
	}
}