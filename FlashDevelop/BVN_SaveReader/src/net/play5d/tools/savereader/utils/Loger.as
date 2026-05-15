package net.play5d.tools.savereader.utils {
	
	import fl.controls.TextArea;
	import flash.text.TextField;
	
	/**
	 * ...
	 * @author tester
	 */
	public class Loger {
		
		private static var _logTextArea:TextArea;
		
		public static var isTrace:Boolean = false;
		
		public function Loger():void {}
		
		public static function init(textArea:TextArea):void {
			_logTextArea = textArea;
		}
		
		public static function log(param:*):void {
			if (_logTextArea == null) {
				return;
			}
			
			var text:String = param.toString();
			if (isTrace) {
				trace(text);
			}
			
			var logTextField:TextField = _logTextArea.textField;
			logTextField.appendText(text + "\n");
			logTextField.scrollV = logTextField.maxScrollV;
		}
	}
}