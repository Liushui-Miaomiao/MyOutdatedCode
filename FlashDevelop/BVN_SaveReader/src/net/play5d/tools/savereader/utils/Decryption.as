package net.play5d.tools.savereader.utils {
	
	import com.adobe.crypto.AES;
	import com.hurlant.util.Hex;
	import flash.utils.ByteArray;
	
	/**
	 * ...
	 * @author tester
	 */
	public class Decryption {
		
		private static var _data:ByteArray;
		
		private static var _key:String;
		private static var _iv:String;
		
		public function Decryption():void {}
		
		public static function init(data:ByteArray, key:String, iv:String):void {
			_data = data;
			_key = key;
			_iv = iv;
		}
		
		public static function start(frontSize:uint = 1024, endSize:uint = 1024):ByteArray {
			if (_data == null) {
				return null;
			}
			
			if (_data.length > frontSize + endSize) {
				var front:ByteArray = new ByteArray();
				var center:ByteArray = new ByteArray();
				var end:ByteArray = new ByteArray();
				
				_data.readBytes(front, 0, frontSize);
				trace("aaaaaaaaaa", _data.length, _data.bytesAvailable)
				_data.readBytes(center, 0, _data.bytesAvailable - endSize);
				
				_data.readBytes(end);
				
				front = decode(front);
				end = decode(end);
				
				var newBytes:ByteArray = new ByteArray();
				newBytes.writeBytes(front);
				newBytes.writeBytes(center);
				newBytes.writeBytes(end);
				
				return newBytes;
			}
			
			return decode(_data);
		}
		
		private static function decode(code:ByteArray):ByteArray {
//			var keyByte:ByteArray = Hex.toArray(_key);
//			var ivByte:ByteArray = Hex.toArray(_iv);
			var i:int;
			var keyByte:ByteArray = new ByteArray();
			var ivByte:ByteArray = new ByteArray();
			var array:Array = [
				0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 
				0x00, 0x00, 0x0a, 0x00
			];
			for (i = 0; i < array.length; i++){
				keyByte.writeByte(array[i]);
			}
			
			array = [
				0x0b, 0x00, 0x0a, 0x00, 0x0e, 0x00, 0x0a, 0x0a, 
				0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x0a/*, 
				0x00, 0x00, 0x00, 0x00,*/
			];
			for (i = 0; i < array.length; i++){
				ivByte.writeByte(array[i]);
			}
			
			
			var aes:AES = new AES(keyByte, ivByte, AES.DEFAULT_CIPHER_NAME, AES.NULL_PADDING);
			return aes.decrypt(code);
		}
	}
}