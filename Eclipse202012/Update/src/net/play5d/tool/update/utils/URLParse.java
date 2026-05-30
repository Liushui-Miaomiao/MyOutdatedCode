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

package net.play5d.tool.update.utils;

public class URLParse {

	/**
	 * 返回一个不会受到缓存影响的 url
	 * 
	 * @param url
	 * @return
	 */
	public static String parse(String url) {
		int 	random 	= (int)(Math.random() * 99999);
		String 	newUrl 	= url + "?random=" + random;
		
		return newUrl;
	}
}
