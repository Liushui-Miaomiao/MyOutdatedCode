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

package net.play5d.tool.update;

import java.io.File;
import java.io.IOException;

import javax.swing.JOptionPane;

import net.play5d.tool.update.data.MyJSON;
import net.play5d.tool.update.utils.MessageBox;
import net.play5d.tool.update.utils.URLParse;

public class Update {
	
	private final static String UPDATE_URL = "http://localhost/version.json";
//	private final static String UPDATE_URL = "https://raw.githubusercontent.com/"
//			+ "Liushui-Miaomiao/"
//			+ "BVN-Update/main/version.json";						// 云端 json 路径
	private final static String LOCAL_URL = "local.json";			// 本地 json 路径

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		String cd        = System.getProperty("user.dir");			// 获取当前运行目录
		String localPath = cd + File.separator + LOCAL_URL;			// 拼接本地 json 路径
		
		MyJSON updateJson = new MyJSON(
				URLParse.parse(UPDATE_URL), 						// 加入一个随机参数防止受到浏览器缓存影响
				true
			);
		MyJSON localJson = new MyJSON(
				localPath, 
				false
			);
		if (!checkJson(updateJson) || !checkJson(localJson)) {		// 有一个加载失败就返回
			MessageBox.show("获取 JSON 文件失败！", "错误", JOptionPane.ERROR_MESSAGE);
			
			return;
		}
		
		String newVer   = updateJson.getValueAsString("ver");		// 获得云端版本
		String localVer = localJson.getValueAsString("ver");		// 获得本地版本
		
//		System.out.println("云端版本：" + newVer);
//		System.out.println("本地版本：" + localVer);
		
		if (newVer == null || localVer == null) {
			MessageBox.show("获取版本号失败！", "错误", JOptionPane.ERROR_MESSAGE);
			
			return;
		}
		
		if (newVer.equals(localVer)) {
			MessageBox.show("当前是最新版本！", "提示");
			
			return;
		}
		
		String downloadLink = updateJson.getValueAsString("download_link");
		String message      = updateJson.getValueAsString("message");
		MessageBox.show(
			"发现新版本：" + newVer + "\n" + 
			"当前版本：" + localVer + "\n" + 
			"下载地址：" + downloadLink + "\n" + 
			"其他信息：" + message,
			"有新版本"
		);
		Runtime.getRuntime().exec("rundll32 url.dll,FileProtocolHandler " + downloadLink);
	}
	
	/**
	 * 检查 json 是否加载完成
	 * 
	 * @param json
	 * @return
	 */
	public static Boolean checkJson(MyJSON json) {
		Boolean b = json.isParsed();
		
		if (!b) {
			MessageBox.show("加载 " + json.getPath() + " 文件失败！", "错误", JOptionPane.ERROR_MESSAGE);
		}
		
		return b;
	}

}
