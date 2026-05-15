package net.play5d.tools.savereader.utils {
	
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.IOErrorEvent;
	import flash.net.URLLoader;
	import flash.net.URLLoaderDataFormat;
	import flash.net.URLRequest;
	import net.play5d.tools.savereader.Main;
	import net.play5d.tools.savereader.event.ReaderEvents;
	import net.play5d.tools.savereader.interfaces.IReader;
	
	/**
	 * ...
	 * @author tester
	 */
	public class Reader extends EventDispatcher implements IReader {
		
		private var _main:Main;
		private var _savePath:String;
		
		private var _request:URLRequest;
		private var _loader:URLLoader;
		
		public var data:*;
		
		public function Reader(main:Main, savePath:String) {
			_main = main;
			_savePath = savePath;
			
			_request = new URLRequest(_savePath);
		}
		
		public function load(dataFormat:String = URLLoaderDataFormat.BINARY):void {
			UIUtils.setAllButtonEnable(false);
			
			_loader = new URLLoader();
			_loader.dataFormat = dataFormat;
			_loader.addEventListener(Event.COMPLETE, onComplete);
			_loader.addEventListener(IOErrorEvent.IO_ERROR, onIOError);
			_loader.load(_request);
		}
		
		private function onComplete(e:Event):void {
			UIUtils.setAllButtonEnable(true);
//			_main.pushData(e.target.data, _savePath);
			
			var readerEvents:ReaderEvents = new ReaderEvents(ReaderEvents.READER_COMPLETE);
			data = e.target.data;
			dispatchEvent(readerEvents);
		}
		
		private function onIOError(e:IOErrorEvent):void {
			dispatchEvent(new IOErrorEvent(ReaderEvents.READER_ERROR));
		}
		
		public function destroy():void {
			_request = null;
			_loader = null;
		}
	}
}