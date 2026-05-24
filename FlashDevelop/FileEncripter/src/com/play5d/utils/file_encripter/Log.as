package com.play5d.utils.file_encripter
{
	import flash.text.TextField;

	public class Log
	{
		private static var _txt:TextField;
		
		public function Log()
		{
		}
		
		public static function init(txt:TextField):void{
			_txt = txt;
		}
		
		public static function log(v:String):void{
			_txt.appendText(v + "\n");
			_txt.scrollV = _txt.maxScrollV;
		}
		
	}
}