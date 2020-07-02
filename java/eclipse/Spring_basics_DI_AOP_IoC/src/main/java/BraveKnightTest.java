import org.junit.jupiter.api.Test;

import java.io.PrintStream;

import static org.mockito.Mockito.*;

public class BraveKnightTest {
    @Test
    public void knightShouldEmbarkOnQuest() {
        Quest mockQuest = mock(Quest.class);
        BraveKnight knight = new BraveKnight(mockQuest);
        knight.embarkOnQuest();
        verify(mockQuest, times(1)).embark();

        BraveKnight knight2 = new BraveKnight(mockQuest);
        knight2.embarkOnQuest();
        verify(mockQuest, times(2)).embark();

        PrintStream pout = new PrintStream(System.out);
        SlayDragonQuest slayDragon = new SlayDragonQuest(pout);

        knight2.setQuest(slayDragon);
        knight2.embarkOnQuest();
        verify(mockQuest, times(2)).embark();
    }
}