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

package net.play5d.tool.update.data;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

public class MyJSON {
	
	private final String CHAR_SET = "utf-8";
	
	private String path;
	
	private JsonParser parser;
	private JsonObject jsonObj;
	
	public MyJSON(String path, Boolean isNet) {
		this.path = path;
		
		String jsonStr = loadJsonFile(isNet);													// 开始加载 json 文件
		if (jsonStr == null) {
			return;
		}
		
		parser  = new JsonParser();
		jsonObj = parser.parse(jsonStr).getAsJsonObject();
	}
	
	/**
	 * 加载 json 文件
	 * 
	 * @param isNet
	 * @return
	 */
	private String loadJsonFile(Boolean isNet) {
		String       jsonStr      = null;
		StringBuffer stringBuffer = new StringBuffer();
		
		try {
			if (isNet) {																		// 判断是网络请求还是本地请求
				URL url = new URL(path);
				HttpURLConnection connection = (HttpURLConnection)url.openConnection();
				
//				connection.setRequestMethod("GET");
//				connection.setRequestProperty(
//						"Accept", 
//						"text/html,"
//						+ "application/xhtml+xml,application/xml;"
//						+ "q=0.9,image/webp,image/apng,*/*;"
//						+ "q=0.8,application/signed-exchange;v=b3;"
//						+ "q=0.9");
//				connection.setRequestProperty("Accept-Encoding", "gzip, deflate, br");
//				connection.setRequestProperty("Accept-Language", "zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6");
//				connection.setRequestProperty(
//						"User-Agent", 
//						"Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
//						+ "AppleWebKit/537.36 (KHTML, like Gecko) "
//						+ "Chrome/101.0.4951.64 Safari/537.36 "
//						+ "Edg/101.0.1210.47");

				connection.connect();
				
//				Map<String, List<String>>map = connection.getHeaderFields();
//				for (String key : map.keySet()) {
//					System.out.println("key：" + key + "，value" + map.get(key));
//				}
				
				int httpResult = connection.getResponseCode();									// 获取请求状态码
//				System.out.println("服务器响应码：" + httpResult);
				
				if (httpResult == HttpURLConnection.HTTP_OK) {									// 如果返回正常
//					int size = connection.getContentLength();									// 数据长度
//					System.out.println(size);
					
					InputStream is = connection.getInputStream();
					InputStreamReader isReader = new InputStreamReader(is, CHAR_SET);
					
					BufferedReader bf = new BufferedReader(isReader);
					String line = null;
					while ((line = bf.readLine()) != null) {
	//					System.out.println(line);
						stringBuffer.append(line + "\n");
					}
					
					isReader.close();
					is.close();
					
					jsonStr = stringBuffer.toString();
				}
			}
			else {																				// 本地请求
				File       file       = new File(path);
				FileReader fileReader = new FileReader(file);
				Reader     reader     = new InputStreamReader(new FileInputStream(file), CHAR_SET);
				
				int line;
				while ((line = reader.read()) != -1) {
					stringBuffer.append((char)line);
				}
				
				fileReader.close();
				reader.close();
				
				jsonStr = stringBuffer.toString();
			}
			
//			System.out.println(jsonStr);
		}
		catch (Exception e) {
//			System.out.println(e);
		}
		
		return jsonStr;
	}
	
	/**
	 * 得到指定 key 的 value
	 * 
	 * @param key
	 * @return
	 */
	public String getValueAsString(String key) {
		return jsonObj.get(key).getAsString();
	}
	
	/**
	 * 判断是否已经解析成功
	 * 
	 * @return
	 */
	public Boolean isParsed() {
		return path != null && jsonObj != null;
	}

	public String getPath() {
		return path;
	}
	public void setPath(String path) {
		this.path = path;
	}

	public JsonObject getJsonObj() {
		return jsonObj;
	}
	public void setJsonObj(JsonObject jsonObj) {
		this.jsonObj = jsonObj;
	}
	
}
