package
{
	
	import com.hurlant.crypto.symmetric.AESKey;
	import com.hurlant.util.Base64;
	import com.play5d.utils.file_encripter.AssetEncripter;
	import com.play5d.utils.file_encripter.Config;
	import com.play5d.utils.file_encripter.Encripter;
	import com.play5d.utils.file_encripter.EncripterMatchFile;
	import com.play5d.utils.file_encripter.Log;
	
	import flash.desktop.ClipboardFormats;
	import flash.desktop.NativeDragManager;
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.NativeDragEvent;
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;
	import flash.text.TextField;
	import flash.utils.ByteArray;
	import flash.utils.getTimer;
	import flash.utils.setTimeout;
	
	import net.play5d.kyo.display.ui.KyoSimpButton;
	
	[SWF(width="800",height="600")]
	public class FileEncripter extends Sprite
	{
		private var _sp:Sprite;
		private var _txt:TextField;
		
		private var _matchFile:EncripterMatchFile = new EncripterMatchFile();
		private var _assetEncripter:AssetEncripter = new AssetEncripter();
		
		public function FileEncripter()
		{
			addEventListener(Event.ADDED_TO_STAGE, initalize);
		}
		
		private function initalize(e:Event):void{
			stage.scaleMode = StageScaleMode.NO_SCALE;
			stage.addEventListener(Event.RESIZE, resizeHandler);
			stage.align = StageAlign.TOP_LEFT;
			
			
			_sp = new Sprite();
			_txt = new TextField();
			
			addBtn('选择资源目录');
			addBtn('选择导出目录');
			
			addBtn('创建校验文件');
			addBtn('读取检验文件');
			
			addBtn('加密资源文件');
			
			Log.init(_txt);
			
			addChild(_sp);
			_sp.addChild(_txt);
			
//			_sp.addEventListener(NativeDragEvent.NATIVE_DRAG_ENTER,dragEnterHandler);
//			_sp.addEventListener(NativeDragEvent.NATIVE_DRAG_DROP,dragDropHandler);
			
			Config.I.load();
			
			Log.log('资源文件加载完成!');
			Log.log('资源文件目录 ' + Config.I.file_path);
			Log.log('导出目录： ' + Config.I.output);
			
			resizeHandler(null);
		}
		
		private var _btns:Array = [];
		private function addBtn(label:String):void{
			var b:KyoSimpButton = new KyoSimpButton(label, 100, 30);
			b.name = label;
			_btns.push(b);
			_sp.addChild(b);
			b.addEventListener(MouseEvent.CLICK, btnHandler);
		}
		
		private function resizeHandler(e:Event):void{
			
			var w:Number = stage.nativeWindow.width;
			var h:Number = stage.nativeWindow.height;
			
			_sp.graphics.clear();
			_sp.graphics.beginFill(0xFFFFFF, 1);
			_sp.graphics.drawRect(0, 0, w, h);
			_sp.graphics.endFill();
			
			_txt.width = w;
			_txt.height = h - 100;
			
			for(var i:int; i < _btns.length; i++){
				_btns[i].x = 10 + i * 120;
				_btns[i].y = h - 100;
			}
		}
		
		private function btnHandler(e:MouseEvent):void{
			switch((e.currentTarget as KyoSimpButton).name){
				case "选择资源目录":
					var file:File = new File(Config.I.file_path);
					file.addEventListener(Event.SELECT, function(e:Event):void{
						Config.I.file_path = file.nativePath;
						Log.log('资源文件目录 ' + Config.I.file_path);
					});
					file.browseForDirectory("选择资源目录");
					break;
				case "选择导出目录":
					var file:File = new File(Config.I.output);
					file.addEventListener(Event.SELECT, function(e:Event):void{
						Config.I.output = file.nativePath;
						Log.log('导出目录： ' + Config.I.output);
					});
					file.browseForDirectory("选择资源目录");
					break;
				case "创建校验文件":
					_matchFile.runEncript(stage);
					break;
				case "读取检验文件":
					_matchFile.readMd5File();
					break;
				case "加密资源文件":
					_assetEncripter.encript(stage);
					break;
			}
		}
		
	}
}