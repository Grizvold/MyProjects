package il.co.ilrd.quizzes;

public class CodeWarsDubstep {
	public static void main(String[] args) {
		System.out.println(longSongDecoder("WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB"));
		System.out.println(SongDecode("WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB"));
	}
	
	public static String longSongDecoder(String song){
		String result = "";
		
		for (String str : song.split("WUB")) {
			result += str + " ";
		}
		result = result.replaceAll("\\s+", " ");
		if(result.charAt(0) == ' ') {
			result = result.substring(1);
		}
		if (result.charAt(result.length() - 1) == ' ') {
			result = result.substring(0, result.length() - 1);
		}
		
		return result;
	  }
	public static String SongDecode(String song) {
	
		return song.replaceAll("(WUB)+", " ").trim();
	}
}
