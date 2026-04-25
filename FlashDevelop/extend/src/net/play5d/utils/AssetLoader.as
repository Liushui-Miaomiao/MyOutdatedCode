package net.play5d.utils {
	
	import flash.display.Loader;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.events.ProgressEvent;
	import flash.events.SecurityErrorEvent;
	import flash.net.URLLoader;
	import flash.net.URLLoaderDataFormat;
	import flash.net.URLRequest;
	import flash.system.LoaderContext;
	import flash.utils.ByteArray;
	
	import sound.SoundByteArray;
	
	public class AssetLoader {
		
		public function AssetLoader():void {}
		
		public function loadXML(url:String, back:Function, fail:Function = null):void {
			decryption(url, function(value:ByteArray):void {
				if (back != null) {
					value.position = 0;
					
					back(new XML(value.readUTFBytes(value.length)));
				}
			}, fail);
		}
		
		public function loadJSON(url:String, back:Function, fail:Function = null):void {
			decryption(url, function(value:ByteArray):void {
				if (back != null) {
					value.position = 0;
					
					var obj:Object = null;
					
					try {
						obj = JSON.parse(value.readUTFBytes(value.length));
					}
					catch (e:Error) {
						trace(e);
					}
					
					back(obj);
				}
			}, fail);
		}
		
		public function loadSwf(url:String, back:Function, fail:Function = null, process:Function = null):void {
			function loadBytesSucc(data:ByteArray):void {
				bytes2display(data, back, fail);
			}
			
			decryption(url, loadBytesSucc, fail, process);
		}
		
		public function loadBitmap(url:String, back:Function, fail:Function = null, process:Function = null):void {
			function loadBytesSucc(data:ByteArray):void {
				bytes2display(data, function(l:Loader):void {
					if (back != null) {
						back(l.content);
					}
				}, fail);
			}
			
			decryption(url, loadBytesSucc, fail, process);
		}
		
		public function loadSound(url:String, back:Function, fail:Function = null, process:Function = null):void {
			decryption(url, function(value:ByteArray):void {
				var snd:SoundByteArray = new SoundByteArray(value);
				
				if (back != null) {
					back(snd);
				}
			}, fail, process);
		}
		
		public function dispose(url:String):void {}
		
		public function needPreLoad():Boolean {
			return false;
		}
		
		public function loadPreLoad(back:Function, fail:Function = null, process:Function = null):void {
			
		}
		
		private function decryption(url:String, back:Function, fail:Function, process:Function = null):void {
			function loadComplete(value:ByteArray):void {
				if (back != null) {
					back(value);
				}
			}
			
			loadBytes("assets/" + url, loadComplete, fail, process);
		}
		
		private function loadBytes(url:String, back:Function, fail:Function = null, progress:Function = null):void {
			var loader:URLLoader = new URLLoader();
			loader.dataFormat = URLLoaderDataFormat.BINARY;
			loader.addEventListener(Event.COMPLETE, onComplete);
			loader.addEventListener(IOErrorEvent.IO_ERROR, onError);
			loader.addEventListener(ProgressEvent.PROGRESS, onProgress);
			
			loader.load(new URLRequest(url));
			
			function onComplete(e:Event):void {
				if (back != null) {
					back(loader.data as ByteArray);
				}
				
				loader = null;
			}
			
			function onError(e:IOErrorEvent):void {
				if (fail != null) {
					fail();
				}
				
				loader = null;
				trace(e);
			}
			
			function onProgress(e:ProgressEvent):void {
				if (progress != null) {
					progress(e.bytesLoaded / e.bytesTotal);
				}
			}
		}
		
		private function bytes2display(bytes:ByteArray, onComplete:Function = null, onError:Function = null):Loader {
			function onLoadComplete(e:Event):void {
				if (onComplete != null) {
					onComplete(loader);
				}
			}
			
			function onLoadError(e:*):void {
				if (onError != null) {
					onError();
				}
				
				trace(e);
			}
			
			var loader:Loader = new Loader();
			loader.contentLoaderInfo.addEventListener(Event.COMPLETE, onLoadComplete);
			loader.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, onLoadError);
			loader.contentLoaderInfo.addEventListener(SecurityErrorEvent.SECURITY_ERROR, onLoadError);
			
			var context:LoaderContext = new LoaderContext();
			context.allowCodeImport = true;
			
			loader.loadBytes(bytes, context);
			
			return loader;
		}
	}
}