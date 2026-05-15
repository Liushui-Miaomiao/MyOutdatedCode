package net.play5d.tools.savereader.event {
	
	import flash.events.Event;
	
	/**
	 * ...
	 * @author tester
	 */
	
	public class ReaderEvents extends Event  {
		
		public static const READER_COMPLETE:String = "readerComplete";
		
		public static const READER_ERROR:String = "readerError";
		
		public function ReaderEvents(type:String, bubbles:Boolean = false, cancelable:Boolean = false):void {
			super(type, bubbles, cancelable);
		}
	}
}