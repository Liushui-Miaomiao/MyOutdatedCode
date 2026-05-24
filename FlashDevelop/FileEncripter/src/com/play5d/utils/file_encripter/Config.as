package com.play5d.utils.file_encripter
{
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;

	public class Config
	{
		private static var _i:Config;
		public static function get I():Config{
			_i ||= new Config();
			return _i;
		}
		
		public var file_path:String;
		public var output:String;
		public var aes:Boolean;
		public var aes_key:String;
		public var aes_iv:String;
		public var encript_kb:int;
		
		public function Config()
		{
		}
		
		public function load():void{
			var f:File = File.applicationDirectory.resolvePath('config.json');
			var fs:FileStream = new FileStream();
			fs.open(f, FileMode.READ);
			var configStr:String = fs.readUTFBytes(fs.bytesAvailable);
			fs.close();
			
			var config:Object = JSON.parse(configStr);
			for(var i:String in config){
				if(hasOwnProperty(i)){
					this[i] = config[i];
					trace(i, '=', config[i]);
				}else{
					throw new Error('未定义参数：'+i)
				}
			}
			
		}
		
	}
}