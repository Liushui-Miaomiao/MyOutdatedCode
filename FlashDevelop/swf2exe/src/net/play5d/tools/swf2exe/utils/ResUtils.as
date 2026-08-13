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
	
	/**
	 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
	 * @version	1.0
	 * @since	4/27/2021 4:59 PM
	 */
	public class ResUtils {
		
		private static var _i:ResUtils;
		
		[Embed(source = "../../../../../../fp/FlashPlayer.exe", mimeType = "application/octet-stream")]
		private var _flashPlayerBin:Class;
		
		/**
		 * Constructor.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:02 PM
		 * 
		 * @return	void
		 */
		public function ResUtils():void {}
		
		/**
		 * Creating a single instance.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:26 PM
		 * 
		 * @return	_i:ResUtils
		 */
		public static function get I():ResUtils {
			if (!_i){
				_i = new ResUtils();
			}
			
			return _i;
		}
		
		/**
		 * Get default player Class.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:28 PM
		 * 
		 * @return	_flashPlayerBin:Class
		 */
		public function getDefaultPlayerClass():Class {
			if (_flashPlayerBin) {
				return _flashPlayerBin;
			}
			
			return null;
		}
		
	}

}