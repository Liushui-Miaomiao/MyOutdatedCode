package net.play5d.tools.savereader.interfaces {
	
	import flash.net.URLLoaderDataFormat;
	
	/**
	 * ...
	 * @author tester
	 */
	public interface IReader {
		
		function load(dataFormat:String = URLLoaderDataFormat.BINARY):void;
		
		function destroy():void;
	}
}