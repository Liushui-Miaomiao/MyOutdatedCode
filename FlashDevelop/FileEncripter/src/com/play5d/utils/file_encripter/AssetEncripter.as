package com.play5d.utils.file_encripter
{
	import flash.display.Stage;
	import flash.events.Event;
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;
	import flash.utils.ByteArray;

	public class AssetEncripter
	{
		private var _files:Vector.<File>;
		private var _count:int = 0;
		private var _finished:int = 0;
		private var _successed:int = 0;
		
		private const _suffixMap:Object = {
			'json': 'j',
			'xml': 'x',
			'swf': 'f',
			'mp3': 'm3',
			'png': 'pi',
			'jpg': 'ji'
		};
		
		private const _stringSuffix:Array = ['json', 'xml', 'txt'];
		
		private var stage:Stage;
		
		public function AssetEncripter()
		{
		}
		
		public function encript(stage:Stage):void{
			Log.log("开始加密资源文件...");
			
			this.stage = stage;
			
			var f:File = new File(Config.I.file_path);
			
			_files = new Vector.<File>();
			getEncriptFiles(f);
			
			_finished = 0;
			_successed = 0;
			_count = _files.length;
			
			if(_files.length > 0){
				stage.addEventListener(Event.ENTER_FRAME, doEncriptFiles);
			}else{
				Log.log("没有需要加密的文件");
			}
		}
		
		private function getEncriptFiles(f:File):void{
			if(!f.exists){
				Log.log("配置文件读取失败，中止");
				return;
			}
			
			if(f.isDirectory){
				var fileList:Array = f.getDirectoryListing();
				for each(var i:File in fileList){
					getEncriptFiles(i);
				}
			}else{
				_files.push(f);
			}
		}
		
		private function doEncriptFiles(e:Event):void{
			if(_files.length < 1){
				stage.removeEventListener(Event.ENTER_FRAME, doEncriptFiles);
				Log.log("加密完成！" + "成功加密" + _successed + "个文件, 失败"+(_count - _successed)+"个文件.");
				return;
			}
			
			try{
				var file:File = _files.shift();
				Log.log("正在加密 "+ file.nativePath +" ("+ _finished + "/" + _count +") ... ");
				
				// 读取源文件流
				var fs:FileStream = new FileStream();
				fs.open(file, FileMode.READ);
				
				var bytes:ByteArray = new ByteArray();
				fs.readBytes(bytes);
				
				fs.close();
				
				
				// 加密的字节数（KB）
				var limitkb:uint = Config.I.encript_kb;
				if(_stringSuffix.indexOf(file.extension) != -1){
					limitkb = 0;
				}
				
				var encriptBytes:ByteArray = Encripter.encriptAsset(bytes, Config.I.aes_key, Config.I.aes_iv, limitkb);
				
				
				// 开始 导出文件
				var sourcePath:String = Config.I.file_path;
				var filePath:String = file.nativePath.replace(sourcePath, "");
				filePath = filePath.substr(1);
				
				
				// 转换后缀名
				var suffixIndex:int = filePath.lastIndexOf(".");
				if(suffixIndex != -1 && _suffixMap[file.extension]){
					filePath = filePath.substr(0, suffixIndex + 1) + _suffixMap[file.extension];
				}
				
				
				// 导出文件
				var newFileUrl:String = Config.I.output + "/" + filePath;
				var newFile:File = new File(newFileUrl);
				
				var fs2:FileStream = new FileStream();
				fs2.open(newFile, FileMode.WRITE);
				fs2.writeBytes(encriptBytes, 0, encriptBytes.bytesAvailable);
				fs2.close();
				
				_successed++;
				Log.log("加密文件 "+ newFile.nativePath +" 完成");
				
			}catch(e:Error){
				Log.log("加密文件 "+ file.nativePath +" 失败");
				trace(e);
			}
			
			_finished++;
		}
		
	}
}