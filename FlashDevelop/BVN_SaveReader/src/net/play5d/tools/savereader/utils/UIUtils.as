package net.play5d.tools.savereader.utils {
	
	import fl.controls.Button;
	import fl.controls.Label;
	import fl.controls.ComboBox;
	import fl.controls.TextArea;
	import fl.core.UIComponent;
	import flash.display.DisplayObject;
	import flash.events.MouseEvent;
	import flash.text.TextFormat;
	import net.play5d.tools.savereader.Main;
	import net.play5d.tools.savereader.data.UIData;
	
	
	/**
	 * ...
	 * @author tester
	 */
	public class UIUtils {
		
		private static var _main:Main;
		
		private static var _textFormat:TextFormat;
		private static var _uiData:Array;
		private static var _ui:Array = [];
		
		public function UIUtils() {}
		
		public static function init(main:Main):void {
			_main = main;
			
			_textFormat = new TextFormat();
			_textFormat.font = "Microsoft YaHei";
			_textFormat.size = 12;
		}
		
		public static function setAllUIStyle():void {
//			trace(_main.numChildren)
			for (var i:int = 0; i < _main.numChildren; i++) {
				var d:* = _main.getChildAt(i);
				if (d is UIComponent) {
//					if (d is ComboBox) {
//						(d as ComboBox).setRendererStyle("textFormat", _textFormat);
//						continue;
//					}
					d.setStyle("textFormat", _textFormat);
				}
			}
		}
		
		public static function setAllUIByUIData():void {
			_uiData = UIData.getUIList();
			
			for (var i:int = 0; i < _uiData.length; i++) {
				var obj:Object = _uiData[i];
				addUI(obj.type, obj.x , obj.y, obj.w, 22, obj.param, obj.funcArray as Array);
			}
		}
		
		
		public static function addUI(cls:Class, x:Number, y:Number, w:Number = 100, h:Number = 22, param:Object = null, funcArray:Array = null):void {
			var ui:* = new cls();
			
			ui.x = x;
			ui.y = y;
			ui.width = w;
			ui.height = h;
			
			if (param != null) {
				for (var property:String in param) {
//					trace(property + ":" + param[property])
					ui[property] = param[property];
				}
			}
			
			if (funcArray != null && funcArray.length > 0) {
				for (var i:int = 0; i < funcArray.length; i++) {
					var funcObj:Object = funcArray[i];
					ui.addEventListener(funcObj.type, funcObj.func);
				}
			}
			
			if (_ui.indexOf(ui) == -1) {
				_ui.push(ui);
			}
			_main.addChild(ui);
		}
		
		public static function setAllButtonEnable(enabled:Boolean):void {
			for (var i:int = 0; i < _ui.length; i++) {
				var ui:* = _ui[i];
				if (ui is UIComponent && ui is Button) {
					ui.enabled = enabled;
				}
			}
		}
		
		public static function getUIByName(name:String):* {
			for (var i:int = 0; i < _ui.length; i++) {
				var ui:* = _ui[i];
				if (ui.name == name) {
					return ui;
				}
			}
		}
	}
}