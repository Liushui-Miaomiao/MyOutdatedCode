package com.play5d.utils.file_encripter
{
	import com.adobe.crypto.MD5;
	
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;
	import flash.utils.ByteArray;
	import flash.utils.getTimer;
	
	import net.play5d.kyo.utils.EncriptUtils;
	

	public class Encripter
	{
		public function Encripter()
		{
		}
		
		public static function encriptFile(fileBytes:ByteArray):String{
			var length:int = fileBytes.length;
			var time:int = getTimer();
			var bytes:ByteArray;
			
			if(length < 1024 * 2){
				bytes = fileBytes;
			}else{
				bytes = new ByteArray();
				bytes.writeBytes(fileBytes, 0, 1024);
				//				bytes.writeBytes(fileBytes, int(length * 0.5), 1024);
				bytes.writeBytes(fileBytes, length - 1024, 1024);
			}
			
			var hash:String = MD5.hashBinary(bytes);
			return hash;
		}
		
		public static function encriptAES(str:String, key:String, iv:String):ByteArray{
			return EncriptUtils.encriptAES(str, key, iv);
		}
		
		public static function decryptAES(code:ByteArray, key:String, iv:String):String{
			return EncriptUtils.decryptAES(code, key, iv);
		}
		
		public static function encriptAsset(bytes:ByteArray, key:String, iv:String, limitKB:uint = 0):ByteArray{
//			var limit:uint = 10 * 1024;
			var limit:uint = limitKB * 1024;
			if(limitKB > 0 && bytes.length > limit){
//				var encriptSize:int = 4 * 1024;
				var encriptSize:int = (limitKB * 0.4) * 1024;
				
				var front:ByteArray = new ByteArray();
				var center:ByteArray = new ByteArray();
				var end:ByteArray = new ByteArray();
				
				bytes.readBytes(front, 0, encriptSize);
				bytes.readBytes(center, 0, bytes.bytesAvailable - encriptSize);
//				bytes.position = bytes.length - encriptSize;
				bytes.readBytes(end);
				
//				trace(bytes.length + "/" + (front.length + center.length + end.length) +"/"+ front.length+"+"+center.length+"+"+end.length+"/");
				
				front = EncriptUtils.encriptAES(front, key, iv);
				end = EncriptUtils.encriptAES(end, key, iv);
				
//				trace("after:"+bytes.length + "/" + (front.length + center.length + end.length) +"/"+ front.length+"+"+center.length+"+"+end.length+"/");
				
//				bytes.writeBytes(front, 0, encriptSize);
//				
//				bytes.position = bytes.length - encriptSize;
//				bytes.writeBytes(end);
				
				// create ---
				var newbytes:ByteArray = new ByteArray();
				newbytes.writeBytes(front);
				newbytes.writeBytes(center);
				newbytes.writeBytes(end);
				
				return newbytes;
			}else{
				return EncriptUtils.encriptAES(bytes, key, iv);
			}
		}
		
		public static function decryptAsset(code:ByteArray, key:String, iv:String):ByteArray{
			return EncriptUtils.decryptAESBytes(code, key, iv);
		}
	}
}