package net.play5d.tools.savereader {
	
	import fl.controls.TextArea;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.events.MouseEvent;
	import flash.net.URLLoader;
	import flash.net.URLLoaderDataFormat;
	import flash.net.URLRequest;
	import flash.text.TextFormat;
	import flash.utils.ByteArray;
	import flash.utils.setTimeout;
	import net.play5d.tools.savereader.event.ReaderEvents;
	import net.play5d.tools.savereader.utils.Decryption;;
	import net.play5d.tools.savereader.utils.Loger;
	import net.play5d.tools.savereader.utils.ObjectUtils;
	import net.play5d.tools.savereader.utils.Reader;
	import net.play5d.tools.savereader.utils.UIUtils;
	import net.play5d.tools.savereader.data.UIData;
	
	/**
	 * ...
	 * @author tester
	 */
	public class Main extends MovieClip {
		
		public const SAVE_PATH:String = "bvnsave.sav";
		public const FIGHTER_XML_PATH:String = "assetss/config/fighter.x";
		private const KEY:String = "kan%ni%zen%me%po!*wo*ye*hen*wu*nai*a*--";
		private const IV:String = "buyao(zenzhala(gaotaiguishouba####(x_x)";
		
		private var _logTextArea:TextArea;
		
		private var _saveReader:Reader;
		private var _xmlReader:Reader;
		
		public var mosouObj:Object;
		public var fighterId:Array = [];
		
		public function Main():void {
			if (stage) { 
				init();
			}
			else {
				addEventListener(Event.ADDED_TO_STAGE, init);
			}
		}
		
		/**
		 * 初始化
		 * 
		 * @param	e
		 */
		private function init(e:Event = null):void {
			removeEventListener(Event.ADDED_TO_STAGE, init);
			
			addFrameScript(0, frame1);
		}
		
		/**
		 * 降低打开时出现空引用异常的概率（躲不掉的）
		 * 
		 * @return
		 */
		public function frame1():void {
			_logTextArea = new TextArea();
			
			setTimeout(function ():void {
				addChild(_logTextArea);
				
				var readerArray:Array = [{
				reader: _saveReader,
				path: SAVE_PATH,
				dataFormat: URLLoaderDataFormat.TEXT
			}, {
				reader: _xmlReader,
				path: FIGHTER_XML_PATH,
				dataFormat: URLLoaderDataFormat.BINARY,
				func: function ():void {
					doNext();
				}
			}];
			drawUI();
			load(readerArray, 0);
				
			}, 250);
		}
		
		/**
		 * 绘制 UI 交互界面
		 */
		private function drawUI():void {
			_logTextArea.x = 310;
			_logTextArea.y = 10;
			_logTextArea.width = 280;
			_logTextArea.height = 380;
			
			Loger.init(_logTextArea);
			Loger.isTrace = true;
			Loger.log("日志输出台...");
		}
		
		/**
		 * 载入数据
		 * 
		 * @param	readerArray	读取器数组
		 * @param	i			索引
		 */
		private function load(readerArray:Array, i:int = 0):void {
			var reader:Reader = readerArray[i].reader;
			var path:String = readerArray[i].path;
			var dataFormat:String = readerArray[i].dataFormat;
			var func:Function = readerArray[i].func;
			
			function onReaderComplete(e:ReaderEvents):void {
				reader.removeEventListener(ReaderEvents.READER_COMPLETE, onReaderComplete);
				reader.destroy();
//				Loger.log(e.target.data);
				pushData(e.target.data, path);
				Loger.log("加载文件 " + path + " 成功！");
				if (func != null) {
					func();
				}
				
				if (++i < readerArray.length) {
					load(readerArray, i);																// 递归加载
				}
			};
			function onReaderIOError(e:IOErrorEvent):void {
				reader.removeEventListener(ReaderEvents.READER_ERROR, onReaderIOError);
				
				Loger.log("加载文件 " + path + " 失败！");
			};
			
			reader = new Reader(this, path);
			reader.addEventListener(ReaderEvents.READER_COMPLETE, onReaderComplete);
			reader.addEventListener(ReaderEvents.READER_ERROR, onReaderIOError);
			reader.load(dataFormat);
		}
		
		private function doNext():void {
//			Loger.log(ObjectUtils.obj2String(mosouObj));
//			Loger.log(String(fighterId));
			
			UIUtils.init(this);
			UIData.init(this);
			UIUtils.setAllUIByUIData();
			UIUtils.setAllUIStyle();
		}
		
		
		/**
		 * 推送数据
		 * 
		 * @param	data	推送的数据
		 * @param	path	数据路径
		 */
		public function pushData(data:*, path:String):void {
			switch (path) {
				case SAVE_PATH:
					var jsonText:String = String(data);
					try {
						mosouObj = JSON.parse(jsonText);
//						mosouObj = mosouObj.mosou;
					}
					catch (e:Error) {
						Loger.log("解析 json 失败！");
					}
					
					break;
				case FIGHTER_XML_PATH:
					Decryption.init(data as ByteArray, KEY, IV);									// 解密 xml 数据
					
					var decryptionData:ByteArray = Decryption.start();
					decryptionData.position = 0;
					trace(decryptionData)
					var fighterXml:XML = XML(decryptionData.readUTFBytes(decryptionData.length));	// 将返回的字节数组以 utf8 文本格式读入并转换为 XML 类型
					var fighter:XMLList = fighterXml.fighter;
					for (var i:int = 0; i < fighter.length(); i++) {
						var id:String = fighter[i].@id;
						if (id.indexOf("xb_") == -1 && id.indexOf("random") == -1) {				// 排除特殊 id
//							trace(id);
							fighterId.push(id);														// 合法 id 加入数组
						}
					}
//					Loger.log(fighterId);
					
					break;
				default :
					Loger.log("未知的路径！");
			}
		}
	}
}