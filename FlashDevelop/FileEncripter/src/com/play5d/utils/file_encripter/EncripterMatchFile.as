package com.play5d.utils.file_encripter
{
	import flash.display.Stage;
	import flash.events.Event;
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;
	import flash.utils.ByteArray;

	public class EncripterMatchFile
	{
		public function EncripterMatchFile()
		{
		}
		
		
		
		
		////////////////////////////////////
				
		public function runEncript(stage:Stage):void{
			
			function getEncriptFiles(f:File):void{
				if(!f.exists) return;
				
				if(f.isDirectory){
					var fileList:Array = f.getDirectoryListing();
					for each(var i:File in fileList){
						getEncriptFiles(i);
					}
				}else{
					var id:String = f.nativePath.replace(Config.I.file_path, "");
					id = id.split('\\').join('/');
					id = id.substr(1);
					outputList.push({id: id, file: f});
				}
			}
			
			function doEncriptFiles(e:Event):void{
				if(outputList.length < 1){
					stage.removeEventListener(Event.ENTER_FRAME, doEncriptFiles);
					Log.log('Finish! count:' + count);
					saveFile();
					return;
				}else{
					var o:Object = outputList.shift();
					var pw:String = Encripter.encriptFile(o.file);
					output[o.id] = pw;
					count ++;
					Log.log(o.id + ' : ' + pw + ' [ ' + count + '/' + outputCount + ' ]');
				}
			}
			
			function saveFile():void{
				Log.log('saving file...');
				
				var sf:File = new File(Config.I.output);
				var fs:FileStream = new FileStream();
				fs.open(sf, FileMode.WRITE);
				var json:String = JSON.stringify(output);
				
				if(Config.I.aes){
					var aes:ByteArray = Encripter.encriptAES(json, Config.I.aes_key, Config.I.aes_iv);
					fs.writeBytes(aes);
				}else{
					fs.writeUTFBytes(json);
				}
				fs.close();
				
				Log.log('saving file successful! Output file to: '+ Config.I.output);
			}
			
			var f:File = new File(Config.I.file_path);
			var outputList:Array = [];
			var outputCount:int = 0;
			var output:Object = {};
			var count:int = 0;
			
			getEncriptFiles(f);
			
			outputCount = outputList.length;
			stage.addEventListener(Event.ENTER_FRAME, doEncriptFiles);
			
		}
				
		
		public function readMd5File():void{
			var md5File:File = new File(Config.I.output);
			var fs:FileStream = new FileStream();
			fs.open(md5File, FileMode.READ);
			
			var bytes:ByteArray = new ByteArray();
			fs.readBytes(bytes);
			
			var decode:String = Encripter.decryptAES(bytes, Config.I.aes_key, Config.I.aes_iv);
			Log.log(decode);
		}
				
		
	}
}