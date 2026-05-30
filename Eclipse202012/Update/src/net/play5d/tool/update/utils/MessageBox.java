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

import javax.swing.JOptionPane;

public class MessageBox {

	/**
	 * 弹出一个提示信息盒子
	 * 
	 * @param message	信息
	 * @param title		标题
	 */
	public static void show(String message, String title) {
		show(message, title, JOptionPane.INFORMATION_MESSAGE);
	}
	
	/**
	 * 弹出一个信息盒子
	 * 
	 * @param message		信息
	 * @param title			标题
	 * @param messageType	信息类型
	 */
	public static void show(String message, String title, int messageType) {
		JOptionPane.showMessageDialog(null, message, title, messageType);
	}
}
