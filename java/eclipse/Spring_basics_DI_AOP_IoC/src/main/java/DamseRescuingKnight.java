public class DamseRescuingKnight implements  Knight{
    private RescueDamselQuest quest;

    //instead of doing this(tightly coupled)
//    public DamseRescuingKnight() {
//        this.quest = new RescueDamselQuest();
//    }

    //do DI by constructor
    public DamseRescuingKnight(RescueDamselQuest quest) {
        this.quest = quest;
    }

    //do DI by setters
    public void setQuest(RescueDamselQuest quest) {
        this.quest = quest;
    }

    public void embarkOnQuest() {
        quest.embark();
    }
}
