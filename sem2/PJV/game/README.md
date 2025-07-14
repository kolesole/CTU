- **Dokumentace pro programátory:**   
    Můj projekt je rozdělen na dvě části:  
    1. model(je zodpovědný za vlastnosti postav, zbraní, materiálů atd.);  
    2. view(je zodpovědný za to, jak bude vypadat hra a co přesně uvidí hráč).  
    
    - **Model(package model):**   
      - **1. Package characters:**  
          - **1) CharacterModel:**   
             Třída, ze které dědí všechny ostatní třídy postav.   
             Obsahuje:  
               - atributy:   
                 (String)strHp, (int)intHp, (String)strDamage, (int)intDamage;  
               - konstruktor:   
                 public CharacterModel(int intHp, int intDamage), převádí intHp i intDamage na 
                 strHp i strDamage pomocí funkce repeat() -> strHp = "_".repeat(intHp) a strDamage = 
                 "-".repeat(intDamage);  
               - gettery všech atributů;  
               - metody:    
                 public void changeHp(int num) a public void changeDamage(int num), které mění 
                 intHp/intDamage a strHp/strDamage.  
          - **2) Beast a DarkKnight:**  
             Třídy nepřátel, které dědí ze třídy CharacterModel a neobsahují nic navíc.  
          - **3) Knight:**   
             Třída hlavní hrdiny, za kterou bude hrát hráč a která dědí ze třídy CharacterModel.   
             Navíc obsahuje:  
               - atributy:   
                 (int)intThirstLvl, (String)strThirstLvl, (int)intDamageToMaterials, 
                 (String)strDamageToMaterials, (int)intProtection, (String)strProtection, (Axe)axe, 
                 (Sword)sword, (Shield)shield, (Inventory)inventory.   
                 Poznámka: na typy posledních čtyř atributů se podíváme o něco později, protože jsou 
                 v jiném balíčku items;   
               - konstruktor:   
                 public Knight(int intHp, int intThirstLvl), převádi intThirstLvl na 
                 strThirstLvl pomocí funkce repeat() -> strThirstLvl = ".".repeat(intThirstLvl) + 
                 nastavuje intDamage na 0, intProtection na 0 -> strProtection = 
                 "|".repeat(intProtection), intDamageToMaterials na 1 -> 
                 strDamageToMaterials = "*".repeat(intDamageToMaterials), sword = new Sword(Nothing), 
                 shield = new Shield(Nothing), axe = new Axe(Nothing), inventory = new Inventory();  
               - gettery všech proměnných;  
               - metody:  
                 public void chahgeThirstLvl(int num), 
                 private void changeDamageToMaterials(int damageToMaterials), 
                 private void changeProtection(int protection), které mění 
                 intThirstLvl/intDamageToMaterials/intProtection a
                 strThirstLvl/strDamageToMaterials/strProtection + 
                 public void upgradeAxe(material Material), 
                 public void upgradeSword(material Material), 
                 public void upgradeShield(material Material), 
                 které používají changery + funkce a typy z balíčku items.weapons.   
      - **2. Package items:**  
          - **1) Třída ItemModel:**  
             Třída, ze které dědí třídy z balíčků materials a food.  
             Obsahuje:  
               - atribut (int)quantity;
               - konstruktor:  
                 public ItemModel(int quantity);
               - getter proměnné quantity;
               - metody:  
                 public void changeQuantity(int num), která mění proměnnou quantity o číslo num;
          - **2) Package food:**  
             Obsahuje:  
               - třídu Apple:  
                 dědí ze třídy ItemModel a neobsahuje nic navíc;    
               - třídu Meat:  
                 dědí ze třídy ItemModel a neobsahuje nic navíc;  
               - třídu Wheat:  
                 dědí ze třídy ItemModel a neobsahuje nic navíc;  
               - třídu Water:  
                 dědí ze třídy ItemModel a neobsahuje nic navíc;  
               - package dishes:  
                 - třídu Pie:  
                   dědí ze třídy ItemModel a neobsahuje nic navíc;  
                 - třídu Soup:  
                   dědí ze třídy ItemModel a neobsahuje nic navíc.  
          - **3) Package materials:**  
             Obsahuje:  
               - třídu Wood:  
                 dědí ze třídy ItemModel a neobsahuje nic navíc;  
               - třídu Iron:
                 dědí ze třídy ItemModel a neobsahuje nic navíc;  
               - třídu Stone:  
                 dědí ze třídy ItemModel a neobsahuje nic navíc.  
          - **4) Package weapons:**  
             Obsahuje:  
               - enum Material:  
                 obsahuje materiály, ze kterých je možné vyrábět zbraně(WOOD, IRON, STONE) a taky stav 
                 NOTHING(kdýž zbraň ještě nebyla vytvořeny);   
               - třídu WeaponModel:
                 Třída, ze které dědí všechny ostatní třídy zbraní.
                 Obsahuje:  
                   - atribut (Material)material;  
                   - konstruktor:  
                     public WeaponModel(Material material);  
                   - getter proměnné material;  
                   - metody:  
                     public void changeMaterial(Material newMaterial), která mění materiál zbraně;  
               - třídu Axe:  
                 Třída, která dědí ze třídy WeaponModel;
                 Obsahuje:  
                   - atribut (int)damageToMaterials;  
                   - konstruktor:  
                     public Axe(Material material), který nastavuje proměnnou damageToMaterials v 
                     závislosti na materiálu:  
                                              NOTHING -> damageToMaterials = 0;  
                                              WOOD -> damageToMaterials = 1;  
                                              IRON -> damageToMaterials = 5;  
                                              STONE -> damageToMaterials = 10;
                   - getter atributu damageToMaterials;  
                   - metody:  
                     public void upgradeAxe(Material newMaterial), která mění atribut 
                     damageToMaterials v závislosti na materiálu;  
                     Poznámka: volá ji metoda upgradeAxe(Material material) ze třídy Knight;      
               - třídu Shield:  
                 Třída, která dědí ze třídy WeaponModel;  
                 Obsahuje:  
                   - atribut (int)protection;  
                   - konstruktor:  
                     public Shield(Material material), který nastavuje atribut protection v 
                     závislosti na materiálu:   
                                              NOTHING -> protection = 0;  
                                              WOOD -> protection = 1;  
                                              IRON -> protection = 3;  
                                              STONE -> protection = 5.  
                   - getter atributu protection;  
                   - metody:  
                     public void upgradeShield(Material newMaterial), která mění atribut 
                     protection v závislosti na materiálu;  
                     Poznámka: volá ji funkce upgradeShield(Material material) ze třídy Knight;  
               - třídu Sword:  
                 Třída, která dědí ze třídy WeaponModel;  
                 Obsahuje:  
                   - atribut (int)damageToCharacters;  
                   - konstruktor:  
                     public Sword(Material material), který nastavuje proměnnou damageToCharacters v 
                     závislosti na materiálu:   
                                              NOTHING -> damageToCharacters = 0;  
                                              WOOD -> damageToCharacters = 2;  
                                              IRON -> damageToCharacters = 6;  
                                              STONE -> damageToCharacters = 10.  
                   - getter atributu damageToCharacters;  
                   - metody:  
                     public void upgradeSword(Material newMaterial), která mění atribut 
                     damageToCharacters v závislosti na materiálu;  
                     Poznámka: volá ji funkce upgradeSword(Material material) ze třídy Knight;  
          - **5) Třída Inventory:**   
             Obsahuje:
               - atributy:  
                 (Water)water, (Iron)iron, (Wheat)wheat, (Wood)wood, (Meat)meat, (Apple)apple, 
                 (Stone)stone, (Pie)pie, (Soup)soup, (int)capacity;  
               - konstruktory:  
                 - prázdný: public Inventory(), nastavuje quantity všech atributů na 0, capacity na 15
                 - neprázdný: public Inventory(int quantityOfWater, int quantityOfIron,  
                                               int quantityOfWheat, int quantityOfWood,  
                                               int quantityOfMeat, int quantityOfApple,  
                                               int quantityOfStone, int capacity),     
                   nastavuje quantity všech atributů na hodnoty předané konstuktoru, pie 
                   a soup na 0;  
              - getter atributu capacity;  
              - metody:  
                - public int quantityOfItems(), vrátí součet, který se skládá z quantity všech atributů->    
                  return water.getQuantity() + iron.getQuantity() + wheat.getQuantity() + 
                  wood.getQuantity() + meat.getQuantity() + apple.getQuantity() + stone.getQuantity() + 
                  pie.getQuantity() + soup.getQuantity();
                - public boolean isFull(), vrátí true, pokud quantityOfItems() se rovná capacity ->  
                  return quantityOfItems == capacity;  
                - public boolean isEmpty(), vrátí true, pokud quantityOfItems() se rovná 0 ->  
                  return quantityOfItems == 0;  
                - public int freePlaces(), vrátí počet volných míst v inventáří ->  
                  return capacity - quantityOfItems;  
                - pak jsou meotdy, které vrátí true, pokud je možné něco vytvořit:  
                  | metoda                                         | podmínka pro true(v inventáře jsou)  |                    
                  | ---------------------------------------------- | ------------------------------------ | 
                  | public boolean isPossibleToCraftAPie()         | 2 apples, 2 waters, 2 wheats         |                                  
                  | public boolean isPossibleToCraftASoup()        | 3 waters, 1 meat                     |                    
                  | public boolean isPossibleToCraftAWoodenAxe()   | 2 woods                              |       
                  | public boolean isPossibleToCraftAWoodenSword() | 3 woods                              |       
                  | public boolean isPossibleToCraftAWoodenShield()| 4 woods                              |       
                  | public boolean isPossibleToCraftAnIronAxe()    | 1 iron, 1 wood                       |              
                  | public boolean isPossibleToCraftAnIronSword()  | 2 irons, 1 wood                      |              
                  | public boolean isPossibleToCraftAnIronShield() | 3 irons, 1 wood                      |              
                  | public boolean isPossibleToCraftAStoneAxe()    | 1 stone, 1 wood                      |               
                  | public boolean isPossibleToCraftAStoneSword()  | 2 stones, 1 wood                     |         
                  | public boolean isPossibleToCraftAStoneShield() | 3 stones, 1 wood                     |               
                - public String isPossibleToCraft(), kontroluje, zda je možné něco vytvořit a vrátí String 
                  s popisem toho, co lze vytvořit. 
      - **3. Třída Action:**  
           Třída obsahuje akce související s hráčem.    
           Obsahuje:    
           - žádné atributy;    
           - prázdný konstruktor:    
             public Actions();    
           - metody:   
             - public void doHit(CharacterModel o1, CharacterModel o2), metoda volá 
               o2.changeHp(-(o1.getIntDamage())), čímž snížuje HP druhého objektu o hodnotu intDamage 
               prvního;  
             - public boolean occurrenceOfDeath(CharacterModel o), vrátí true, pokud intHp objektu se 
               rovná 0. Byla vytvořena pro indentifikaci smrti postav;    
             - public boolean occurrenceOfPlayersDeath(Knight knight), vrátí true, pokud intHp nebo
               intThirstLvl hráče se rovná 0. Byla vytvořena pro indentifikaci smrti hráče;    
             - pak jsou metody, které jsou zodpovědné za sbírání předmětů:  
               - public boolean collectAnApple(Knight knight), public boolean collectAMeat(Knight knight), 
                 public boolean collectAWheat(Knight knight), public boolean collectAWater(Knight knight).
                 Metody, které volají changeQuantity(+1) pro knight.inventory.apple/meat/wheat/water a 
                 vrátí true, pokud knight.inventory.isFull() == false, v opačném případě vrátí false;  
               - public boolean collectAWood(Knight knight), public boolean collectAnIron(Knight knight),
                 public boolean collectAStone(Knight knight).
                 Metody, které volají 
                 changeQuantity(Math.min(knight.getIntDamageToMaterials(),knight.inventory.freePlaces()) 
                 pro knight.inventory.wood/iron/stone a vrátí true, pokud knight.inventory.isFull == false, 
                 v opačném přípádě vrátí false;  
             - public boolean drinkWater(Knight knight).
               Metoda, která volá knight.changeThirstLvl(+1), knight.inventory.water.changeQuantity(-1) a 
               vrátí true, pokud knight.inventory.water.getQuantity != 0, v opáčném případě vrátí false;  
             - public boolean eatApple(Knight knight), public boolean eatPie(Knight knight), 
               public boolean eatSoup(Knight knight).
               Metody, které volají knight.changeHp(num)  
               | food  | num |
               | ----- | --- |
               | apple | 1   |
               | pie   | 3   |   
               | soup  | 5   |,  
                         
               knight.inventory.apple/pie/soup.changeQuantity(-1) a vrátí true, 
               pokud knight.inventory.apple/pie/soup.getQuantity() != 0, v opčném přípádě vrátí false;  
             - pak jsou metody pro craft jídla:    
               - public boolean craftAPie(Knight knight).  
                 Metoda, která volá  knight.inventory.apple/water/wheat.changeQuantity(-2), 
                 knight.inventory.pie.changeQuantity(1+) a vrátí true, pokud 
                 knight.inventory.isPossibleToCraftAPie() == true, v opáčném případě vrátí false;
               - public boolean craftASoup(Knight knight).  
                 Metoda, která volá knight.inventory.water.changeQuantity(-3), 
                 knight.inventory.meat.changeQuantity(-1), knight.inventory.soup.changeQuantity(+1) a 
                 vrátí true, pokud knight.inventory.isPossibletoCraftAsoup == true, v opáčném případě vrátí
                 false;  
             - pak jsou metody pro craft zbraní:
               - ze dřeva:
                 public boolean craftAWoodenAxe(Knight knight), 
                 public boolean craftAWoodenSword(Knight knight),
                 public boolean craftAWoodenShield(Knight knight), volají 
                 knight.inventory.wood.changeQuantity(num)  
                 | typ zbraně | num |
                 | ---------- | --- |
                 | Axe        |  -2 |
                 | Sword      |  -3 |
                 | Shield     |  -4 |,  
  
                 knight.upgradeAxe/Sword/Shield(WOOD) a vrátí true, pokud 
                 knight.inventory.isPossibleToCraftAWoodenAxe/Sword/Shield() == true, v opáčném případě 
                 vrátí false;
               - ze železa:  
                 public boolean craftAnIronAxe(Knight knight), 
                 public boolean craftAnIronSword(Knight knight),
                 public boolean craftAnIronShield(Knight knight), volají
                 knight.inventory.wood.changeQuantity(-1), knight.inventory.iron.changeQuantity(num)  
                 | typ zbraně | num |
                 | ---------- | --- |
                 | Axe        |  -1 |
                 | Sword      |  -2 |
                 | Shield     |  -3 |,  
                 
                 knight.upgradeAxe/Sword/Shield(Iron) a vrátí true, pokud 
                 knight.inventory.isPossibleToCraftAnIronAxe/Sword/Shield() == true, v opáčném případě 
                 vrátí false; 
               - z kamene:  
                 public boolean craftAStoneAxe(Knight knight), 
                 public boolean craftAStoneSword(Knight knight),
                 public boolean craftAStoneShield(Knight knight), volají  
                 knight.inventory.wood.changeQuantity(-1), knight.inventory.iron.changeQuantity(num)  
                 | typ zbraně | num |
                 | ---------- | --- |
                 | Axe        |  -1 |
                 | Sword      |  -2 |
                 | Shield     |  -3 |,  

                 knight.upgradeAxe/Sword/Shield(Stone) a vrátí true, pokud 
                 knight.inventory.isPossibleToCraftAStoneAxe/Sword/Shield() == true, v opáčném případě 
                 vrátí false;
    - **View:**   
        Poznámka: View byl vytvořen pomocí editoru SceneBuilder, proto bych chtěl vysvětlit, jaké 
                  atributy jsou převzaty do třídy GameController z fxml.  
        - **FXML atributy:**          
              - (Anchor pane)pane - hlavní plátno, na kterém jsou umístěny všechny objekty;  
              - (ImageView)playerImage - obrázek hráče + (Knight)player - vytvoření hráče s HP = 10 a 
                ThirstLvl = 20;  
              - (ImageView)heart1/.../10 - obrázky, které zobrazují HP hráče;    
              - (ImageView)shield1/.../5 - obrázky, které zobrazují protection points hráče;    
              - (ImageView)water1/.../20 - obrázky, které zobrazují thirst lvl hráče;  
              - (ImageView)flagImage - obrázek vlajky;  
              - (ImageView)campFireImage - obrázek ohně;  
              - (ImageView)apple1/.../13 - obrázky, které zobrazují jablka, která si hráč může 
                nasbírat;  
              - (ImageView)treeTop1/.../11 a (ImageView)treeTrunk1/.../11 - obrázky, které zobrazují 
                stromy, které hráč může pokácet;    
              - (ImageView)wheat1/.../18 - obrázky, které zobrazují pšenici;
              - (Label)infoLabel, infoCraftsDishesLabel, infoCraftsWeaponsLabel - labely, které 
                obsahují zprávy pro hráče;  
              - (Label)quantityOfApple, quantityOfIron, quantityOfMeat, quantityOfPie, quantityOfSoup,
                quantityOfStone, quantityOfWater, quantityOfWheat, quantityOfWood - labely, které 
                obsahují kolik předmětů je v inventáře;  
              - (ImageView)woodenAxe, woodenSword, woodenShield, ironAxe, ironSword, ironShield, 
                stoneAxe, stoneSword, stoneShield - obrázky zbraní v inventáři;    
              - (ImageView)obj1, obj2, obj3 - obrázky, které jsou odstraněny při otevření 2. úrovně;  
              - (ImageView)boarImage1, boarImage2, boarImage3, boarImage4, boarImage5, boarImage6, 
                boarImage7 - obrázky, které zobrazují kance na 2. úrovni;  
              - (Beast)boar1 = new Beast(60, 1), boar2 = new Beast(60, 1),  
                       boar3 = new Beast(60, 1), boar4 = new Beast(60, 1),  
                       boar5 = new Beast(60, 1), boar6 = new Beast(60, 1),  
                       boar7 = new Beast(60, 1) - kanci z druhé úrovně v typu Beast;  
              - (Label)additionSign1, additionSign2, additionSign3, additionSign4, additionSign5,
                additionSign6, additionSign7, additionSign8, additionSign9 - labely pro přídavné znaky 
                používané na tabu vytváření;  
              - (ImageView) craftsApple, craftsCell1/.../52, craftsIron1/.../3, 
                craftsIronAxe/Sword/Shield, craftsWoodenAxe/Sword/Shield, craftsStoneAxe/Sword/Shield
                craftsMeat, craftsPie, craftsSoup, craftsStone1/.../3, craftsWater1/.../2,  
                craftsWheat, craftsWood1/.../9 - obrázky pro craft různých předmětů;  
              - (Label)equalSign1/.../9 - labely pro rovnítko používané na kartě vytváření;   
              - (ImageView)inventory, inventoryApple, inventoryIron, inventoryMeat, inventoryPie,
                inventorySoup, inventoryStone, inventoryWater, inventoryWood, inventoryWheat - 
                obrázky pro položky, které tvoří součást inventáře;  
              - (Label)quantityOfApple1, quantityOfIron1/.../3, quantityOfMeat1,
                quantityOfStone1/.../3, quantityOfWater1/.../2, quantityOfWheat1, 
                quantityOfWood1/.../9 - labely pro množství různých craft předmětů;    
              - (ImageView)iron1/.../10 - obrázky železa, které si hráč může vzít a doplnit zásobu;  
              - (Label)gameOverLabel1, gameOverLabel2, gameOverLabel11, gameOverLabel21 - 
                labely, které se objeví, když hráč zemře;  
              - (int)upImageIndex = 1, downImageIndex = 1, rightImageIndex = 1, leftImageIndex = 1,
                hitImageIndex = 0, campFireIndex = 1, flagIndex = 1 - indexy, které jsou vytvořeny pro 
                sprite obrázky;  
              - (boolean)up = false, right = false, down = false, left = false, 
                playerDirectionIsUp = false, playerDirectionIsRight = false, 
                playerDirectionIsDown = false, playerDirectionIsLeft = false, 
                collectAnApple, collectAWheat, collectAWater, collectAMeat, 
                isInventoryOpen, hit = false, isRunning = false - atributy pro interakci mezi 
                GameController a GameApplication;    
              - (boolean)isWoodenAxe = true, isWoodenSword = false, isWoodenShield = false, 
                isIronAxe = false, isIronSword = false, isIronShield = false, isStoneAxe = false, 
                isStoneSword = false, isStoneShield = false - atributy ke sledování zbraní, které hráč 
                má;    
              - Actions actions = new Actions(),  
                Crafts crafts = new Crafts(),  
                Consumers consumers = new Consumers(),  
                Collectors collectors = new Collectors(),  
                Setters setters = new Setters(),  
                LevelChanger levelChanger = new LevelChanger(),  
                Movement movement - další projektové třídy;  
              - (Stage)stage - atribut pro předání mane stage z GameApplication;    
              - (int)iteration = 0 - sledování počtu iterací;               
              - (boolean)secondLevelRunning = false - sledování, zda běží druhá úroveň;       
        - **1. Třída Setters:**   
            - Třída, která je zodpovědná za nastavení úrovně HP/ochrany a žízně.    
            - má prázdný konstruktor;  
            - metody:   
              - public void setHp(Knight player, ImageView[] hearts) - metoda, která je zodpovědná 
                za nastavení obrázků srdce;       
              - public void setProtection(Knight player, ImageView[] shields) - metoda, která je 
                zodpovědná za nastavení obrázků štítu;      
              - public void setThirstLvl(Knight player, ImageView[] water) - metoda, která je 
                zodpovědná za nastavení obrázků vody;  
        - **2. Třída Movement:**     
            - Třída, která je zodpovědná za pohyb hráče, 
              kontroluje, aby souřadnice hráče nesouhlasily s neviditelnými zdmi.     
            - Pole:   
              - private ImageView playerImage - obrázek hráče;   
            - má konstruktor s parametry:  
              - public Movement(ImageView playerImage) - inicializuje obrázek hráče.  
            - metody:   
              - public boolean isPossibleMoveToLeft() - metoda, která zjišťuje, zda je možné 
                pohybovat se doleva;  
              - public boolean isPossibleMoveToRight(ImageView obj1, ImageView obj2, ImageView obj3) - 
                metoda, která zjišťuje, zda je možné pohybovat se doprava. Také má parametry, které 
                zmizí při otevření druhé úrovně;  
              - public boolean isPossibleMoveToUp() - metoda, která zjišťuje, zda je možné 
                pohybovat se nahoru bez parametrů;  
              - public boolean isPossibleMoveToDown() - metoda, která zjišťuje, zda je možné 
                pohybovat se dolů bez parametrů;  
        - **3. Třída Collectors:**  
            - Třída, která je zodpovědná za sbírání předmětů;    
            - má prázdný konstruktor;   
            - metody:  
              - public void collectAnApple(ImageView[] apples, Actions actions, ImageView playerImage, 
                                           Knight player, Label infoLabel, Label quantityOfApple) - 
                - Metoda, která je zodpovědná za sbírání jablek. Kontroluje, zda hráčův obraz 
                  (playerImage) koliduje s obrazem jablka (apples). Pokud ano a inventář není plný, 
                  přidá jablko do inventáře a aktualizuje odpovídající Label.    
              - public void collectAWheat(ImageView[] wheat, Actions actions, ImageView playerImage, 
                                          Knight player, Label infoLabel, Label quantityOfWheat) - 
                - Metoda, která je zodpovědná za sbírání pšenice. Kontroluje, zda hráčův obraz 
                  (playerImage) koliduje s obrazem pšenice (wheat). Pokud ano a inventář není plný, 
                  přidá pšenici do inventáře a aktualizuje odpovídající Label.    
              - public void collectAWater(ImageView playerImage, Knight player, Actions actions, Label 
                                          infoLabel, Label quantityOfWater) -  
                - Metoda, která je zodpovědná za sbírání vody. Kontroluje, zda hráčův obraz 
                   (playerImage) je ve specifickém rozsahu souřadnic. Pokud ano a inventář není plný, 
                   přidá vodu do inventáře a aktualizuje odpovídající Label.     
              - public void collectAWood(ImageView[] treeTops, ImageView[] treeTrunks, Actions actions, 
                                         ImageView playerImage, Knight player, Label infoLabel, Label 
                                         quantityOfWood) - 
                - Metoda, která je zodpovědná za sbírání dřeva. Kontroluje, zda hráčův obraz 
                  (playerImage) koliduje s obrazem vrcholků stromů (treeTops) a kmenů stromů 
                  (treeTrunks). Pokud ano a inventář není plný, přidá dřevo do inventáře a aktualizuje 
                  odpovídající Label.    
              - public void collectAnIron(ImageView[] iron, Actions actions, ImageView playerImage, 
                                          Knight player, Label infoLabel, Label quantityOfIron) - 
                - Metoda, která je zodpovědná za sbírání železa. Kontroluje, zda hráčův obraz 
                  (playerImage) koliduje s obrazem železa (iron). Pokud ano a inventář není plný, přidá 
                  železo do inventáře a aktualizuje odpovídající Label.    
              - public void collectAMeat(ImageView[] boarsImages, Beast[] boars, Actions actions, 
                                         ImageView playerImage, Knight player, Label infoLabel, Label 
                                         quantityOfMeat) - 
                - Metoda, která je zodpovědná za sbírání masa, pokud je kanec (boar) mrtvý. Kontroluje, 
                zda hráčův obraz (playerImage) koliduje s obrazem kance (boarsImages) a zda je kanec 
                mrtvý. Pokud ano a inventář není plný, přidá maso do inventáře a aktualizuje 
                odpovídající Label.      
        - **4. Třída Consumers:**  
            - Třída, která je zodpovědná za konzumaci jídla a vody.  
            - má konstruktor bez parametrů.  
            - metody:  
              - public void drinkWater(MouseEvent event, Actions actions, Knight player, Label 
                                       infoLabel, Label quantityOfWater) - 
                - Metoda, která je zodpovědná za konzumaci vody. Kontroluje, zda bylo stisknuto pravé 
                  tlačítko myši (MouseButton.SECONDARY). Pokud ano a hráč může pít vodu, odečte se 
                  jedna voda z inventáře a aktualizuje odpovídající Label.    
              - public void eatApple(MouseEvent event, Actions actions, Knight player, Label infoLabel, 
                                     Label quantityOfApple) - 
                - Metoda, která je zodpovědná za konzumaci jablka. Kontroluje, zda bylo stisknuto pravé 
                  tlačítko myši (MouseButton.SECONDARY). Pokud ano a hráč může jíst jablko, odečte se 
                  jedno jablko z inventáře a aktualizuje odpovídající Label.    
              - public void eatPie(MouseEvent event, Actions actions, Knight player, Label infoLabel, 
                                   Label quantityOfPie) - 
                - Metoda, která je zodpovědná za konzumaci koláče. Kontroluje, zda bylo stisknuto 
                  pravé tlačítko myši (MouseButton.SECONDARY). Pokud ano a hráč může jíst koláč, odečte 
                  se jeden koláč z inventáře a aktualizuje odpovídající Label.    
              - public void eatSoup(MouseEvent event, Actions actions, Knight player, Label infoLabel, 
                                    Label quantityOfSoup) - 
                - Metoda, která je zodpovědná za konzumaci polévky. Kontroluje, zda bylo stisknuto 
                  pravé tlačítko myši (MouseButton.SECONDARY). Pokud ano a hráč může jíst polévku, 
                  odečte se jedna polévka z inventáře a aktualizuje odpovídající Label.    
        - **5. Třída Crafts:**  
            - Třída, která zajišťuje funkce pro výrobu předmětů.  
            - má konstruktor bez parametrů.  
            - metody:  
              - public void craftAPie(MouseEvent event, Knight player, Actions actions, Label 
                                      infoCraftsDishesLabel, Label quantityOfPie, Label 
                                      quantityOfApple, Label quantityOfWheat, Label quantityOfWater) - 
                - Metoda pro výrobu koláče. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč má dostatek surovin, odečte se požadované 
                  množství surovin z inventáře a přidá se jeden koláč. Aktualizuje odpovídající Label.
              - public void craftASoup(MouseEvent event, Knight player, Actions actions, Label 
                                       infoCraftsDishesLabel, Label quantityOfSoup, Label 
                                       quantityOfWater, Label quantityOfMeat) - 
                - Metoda pro výrobu polévky. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč má dostatek surovin, odečte se požadované 
                  množství surovin z inventáře a přidá se jedna polévka. Aktualizuje odpovídající 
                  Label.  
              - public void craftAWoodenAxe(MouseEvent event, Knight player, Actions actions, Label 
                                            infoCraftsWeaponsLabel, ImageView woodenAxe, Label 
                                            quantityOfWood) - 
                - Metoda pro výrobu dřevěné sekery. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč nemá již dřevěnou sekeru, a má dostatek 
                  surovin, odečte se požadované množství surovin z inventáře a přidá se jedna dřevěná 
                  sekera. Aktualizuje odpovídající Label a zobrazí obrázek dřevěné sekery.  
              - public void craftAWoodenSword(MouseEvent event, Knight player, Actions actions, Label 
                                              infoCraftsWeaponsLabel, ImageView woodenSword, Label 
                                              quantityOfWood) - 
                - Metoda pro výrobu dřevěného meče. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč nemá již dřevěný meč, a má dostatek 
                  surovin, odečte se požadované množství surovin z inventáře a přidá se jeden dřevěný 
                  meč. Aktualizuje odpovídající Label a zobrazí obrázek dřevěného meče.  
              - public void craftAWoodenShield(MouseEvent event, Knight player, Actions actions, Label 
                                               infoCraftsWeaponsLabel, ImageView woodenShield, Label 
                                               quantityOfWood) - 
                - Metoda pro výrobu dřevěného štítu. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč nemá již dřevěný štít, a má dostatek 
                  surovin, odečte se požadované množství surovin z inventáře a přidá se jeden dřevěný 
                  štít. Aktualizuje odpovídající Label a zobrazí obrázek dřevěného štítu.   
              - public void craftAnIronAxe(MouseEvent event, Knight player, Actions actions, Label 
                                           infoCraftsWeaponsLabel, ImageView ironAxe, Label 
                                           quantityOfWood, Label quantityOfIron) - 
                - Metoda pro výrobu železné sekery. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč nemá již železnou sekeru, a má dostatek 
                  surovin, odečte se požadované množství surovin z inventáře a přidá se jedna železná 
                  sekera. Aktualizuje odpovídající Label a zobrazí obrázek železné sekery.   
              - public void craftAnIronSword(MouseEvent event, Knight player, Actions actions, Label 
                                             infoCraftsWeaponsLabel, ImageView ironSword, Label 
                                             quantityOfWood, Label quantityOfIron) - 
                - Metoda pro výrobu železného meče. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč nemá již železný meč, a má dostatek 
                  surovin, odečte se požadované množství surovin z inventáře a přidá se jeden železný 
                  meč. Aktualizuje odpovídající Label a zobrazí obrázek železného meče.    
              - public void craftAStoneAxe(MouseEvent event, Knight player, Actions actions, Label 
                                           infoCraftsWeaponsLabel, ImageView stoneAxe, Label 
                                           quantityOfWood, Label quantityOfStone) - 
                - Metoda pro výrobu kamenné sekery. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč nemá již kamennou sekeru, a má dostatek 
                  surovin, odečte se požadované množství surovin z inventáře a přidá se jedna kamenná 
                  sekera. Aktualizuje odpovídající Label a zobrazí obrázek kamenné sekery.  
              - public void craftAStoneSword(MouseEvent event, Knight player, Actions actions, Label 
                                             infoCraftsWeaponsLabel, ImageView stoneSword, Label 
                                             quantityOfWood, Label quantityOfStone) - 
                - Metoda pro výrobu kamenného meče. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč nemá již kamenný meč, a má dostatek 
                  surovin, odečte se požadované množství surovin z inventáře a přidá se jeden kamenný 
                  meč. Aktualizuje odpovídající Label a zobrazí obrázek kamenného meče.  
              - public void craftAStoneShield(MouseEvent event, Knight player, Actions actions, Label 
                                              infoCraftsWeaponsLabel, ImageView stoneShield, Label 
                                              quantityOfWood, Label quantityOfStone) - 
                - Metoda pro výrobu kamenného štítu. Kontroluje, zda bylo stisknuto pravé tlačítko myši 
                  (MouseButton.SECONDARY). Pokud ano a hráč nemá již kamenný štít, a má dostatek 
                  surovin, odečte se požadované množství surovin z inventáře a přidá se jeden kamenný 
                  štít. Aktualizuje odpovídající Label a zobrazí obrázek kamenného štítu.  
        - **6. Třída LevelChanger:**  
            - Třída, která je zodpovědná za změnu úrovní ve hře.   
            - má konstruktor bez parametrů.  
            - Pole:  
              - isFirstLvl (typ boolean): Určuje, zda se hráč nachází na první úrovni.  
              - isSecondLvl (typ boolean): Určuje, zda se hráč nachází na druhé úrovni.  
              - isThirdLvl (typ boolean): Určuje, zda se hráč nachází na třetí úrovni.  
            - metody:
              - public void change1stLvlOn2ndLvl(Stage stage, ImageView playerImage, AnchorPane pane, 
                                                 ImageView obj1, ImageView obj2, ImageView obj3, 
                                                 ImageView[] hearts, ImageView[] shields, ImageView[] 
                                                  water, Label[] labels, ImageView[] inventoryItems) -  
                - Metoda, která je zodpovědná za přechod z první úrovně na druhou.  
              - public void change2ndLvlOn1stLvl(Stage stage, ImageView playerImage, AnchorPane pane, 
                                                 ImageView[] hearts, ImageView[] shields, ImageView[] 
                                                 water, Label[] labels, ImageView[] inventoryItems) -   
                - Metoda, která je zodpovědná za návrat z druhé úrovně na první.  

              - public void change2ndLvlOn3rdLvl() - metoda není implementována.  
              - public void change3rdLvlOn2ndLvl() - metoda není implementována.  
        - **7. Třída BeastThread:**  
            - Třída, která implementuje rozhraní Runnable a představuje vlákno pro řízení chování 
              kanců.  
            - má konstruktor: public BeastThread(ImageView boarImage, Beast boar, ImageView 
                                                 playerImage, Knight player, Actions actions).   
            - Atributy:  
              - boarImage: ImageView reprezentující obrázek kance.  
              - boar: Instance třídy Beast představující kance.  
              - playerImage: ImageView reprezentující obrázek hráče.  
              - player: Instance třídy Knight představující hráče.  
              - actions: Instance třídy Actions pro provádění akcí.  
              - running: Boolean hodnota indikující běžící stav vlákna.  
              - MOVEMENT_SPEED: Konstanta pro rychlost pohybu kance.  
              - upImageIndex, leftImageIndex, downImageIndex, rightImageIndex, hitImageIndex, 
                dieImageIndex: Indexy obrázků pro různé akce kance.  
              - boarDirectionIsUp, boarDirectionIsLeft, boarDirectionIsDown, boarDirectionIsRight: 
                Boolean hodnoty reprezentující směr pohybu kance.  
              - hit, die: Boolean hodnoty indikující útok nebo smrt kance.  
              - walkIteration, hitIteration, deathIteration: Počítadla iterací pro různé akce kance.  
              - moveX, moveY: Atributy pro posun divokého vepřa na ose X a Y.  
            - Metody:
              - public void run(): Metoda implementovaná z rozhraní Runnable, řídí pohyb, útoky a smrt 
                kance.     
              - private void updateBoarWalk(double moveX, double moveY): Metoda pro aktualizaci pohybu 
                kance na základě posunu na osách X a Y.    
              - private void do_hit(): Metoda pro provedení útoku kance.  
              - occurrenceOfBeastDeath(): Metoda pro vyvolání smrti kance a postupné změny obrázků.  
              - stop(): Metoda pro zastavení vlákna.  
        - **8. Třída GameController:**  
            - Atributy jsou popsány na začátku.  
            - nemá konstruktor.  
            - Metody:  
              - AnimationTimer animationTimer: Zde je vytvořen nový AnimationTimer a přepsána metoda 
                handle, ve které jsou definovány akce, které se budou provádět v každém snímku animace 
                do smrti hráče.   
              - public void setStage(Stage stage): Metoda, která přenýší stage z GameApplication.  
              - public void stopAnimationTimer(): Metoda, která zastavuje AnimationTimer.  
              - private void openInventory(): Metoda, která otevře inventář a zviditelní prvky.   
              - private void closeInventory(): Obracená metoda předchozí metody.   
              - private void collectAnApple(), private void collectAWheat(), 
                private void collectAWater(), private void collectAMeat(), private void collectAWood(), 
                private void collectAnIron(): Metody, které volají stejné metody ze třídy Collectors a 
                předávají pole typu ImageView.  
              - private void setHp(), private void setProtection(), private void setThirstLvl(): 
                Metody, které volají stejné metody ze třídy Setters a předávají pole typu ImageView.  
              - private void changeLevel(): Metoda, která volá metody ze třídy LevelChanger.  
              - void drinkWater(MouseEvent event), void eatApple(MouseEvent event), 
                void eatPie(MouseEvent event), void eatSoup(MouseEvent event), 
                void craftAPie(MouseEvent event), void craftASoup(MouseEvent event), 
                void craftAWoodenAxe(MouseEvent event), void craftAWoodenSword(MouseEvent event), 
                void craftAWoodenShield(MouseEvent event), void craftAnIronAxe(MouseEvent event), 
                void craftAnIronSword(MouseEvent event), void craftAnIronShield(MouseEvent event), 
                void craftAStoneAxe(MouseEvent event), void craftAStoneSword(MouseEvent event), 
                void craftAStoneShield(MouseEvent event): Metody z FXML souboru, které volají stejné
                metody ze tříd Crafts a Consumers.    
              - void initialize(): Metoda, která inicializuje animationTimer.  
    - **Třídy které nejsou ve view a model**:  
        - **1. Třída MyLogger:**  
            - Třída s dodatky k běžné třídě Logger.  
            - Atributy: (FileHandler)fileHandler, který slouží k manipulaci se souborem pro zápis 
              logovacích zpráv.    
            - má prázdný konstruktor.             
            - Metody:  
              - public void enableLogging(Logger logger, String fileName) throws IOException:  
                Tato metoda umožňuje zapnout logování a vytvořit soubor pro zápis logovacích zpráv.  
                - Parametry:  
                  - logger typu Logger je instance loggeru, ze kterého budou logovací zprávy zapisovány 
                    do souboru.   
                  - fileName typu String je název souboru, do kterého se budou logovací zprávy 
                    zapisovat.  
                  - Pokud soubor s daným názvem neexistuje nebo je logger null, metoda nejprve soubor 
                    smaže a poté vytvoří nový.   
              - public void disableLogging(Logger logger):  
                Tato metoda slouží k vypnutí logování pro daný logger.  
        - **2. Třída GameApplication:**  
            - Třída, která rozšiřuje třídu Application a slouží k řízení hry. 
            - Atributy:   
              - public static final Logger movementLogger = Logger.getLogger(Movement.class.getName()), 
                public static final LoggercollectorsLogger = 
                = Logger.getLogger(Collectors.class.getName()), 
                public static final Logger consumersLogger = 
                = Logger.getLogger(Consumers.class.getName()), 
                public static final Logger craftsLogger = Logger.getLogger(Crafts.class.getName()), 
                public static final Logger gameControllerLogger = 
                = Logger.getLogger(GameController.class.getName()), 
                public static final Logger levelChangerLogger = 
                = Logger.getLogger(LevelChanger.class.getName()), 
                public static final Logger gameApplicationLogger = 
                = Logger.getLogger(GameApplication.class.getName()), 
                public static final Logger beastThreadLogger = 
                = Logger.getLogger(BeastThread.class.getName()) - 
                Deklarace logovacích instancí:
                Pro třídy jsou vytvořeny statické logovací instance. Každá 
                instance loggeru má svůj vlastní název podle jména třídy.  
              - MyLogger myLogger - Deklarace instance MyLogger.  
              - (boolean)isRunning - Proměnná typu boolean, která indikuje, zda hra běží nebo ne.
            - Metody:  
              - public void start(Stage stage) throws IOException:    
                - Přepsaná metoda z třídy Application, která se volá při spuštění aplikace. Zde jsou 
                  smazány existující logovací soubory a inicializuje se hlavní okno.
              - public void secondStart(Stage stage) throws IOException:  
                - Metoda pro opakované spuštění hry, která inicializuje hlavní okno bez vytváření 
                  logování.  
              - private void showMenu(Stage stage) throws IOException:  
                - Metoda pro zobrazení menu hry(výtvořené bez použití editoru). Vytváří scénu s 
                  tlačítky pro spuštění/ukončení hry a možností povolení / zakázání logování.  
              - private void showGame(Stage stage) throws IOException:  
                - Metoda pro zobrazení herní scény. Načte FXML soubor pro herní pohled, nastaví herní 
                  ovladač a naslouchá klávesovým a myším událostem pro ovládání hry. Také spouští herní 
                  časovač pro průběžné snižování úrovně žízně hráče.    
              - public static void main(String[] args):  
                - Hlavní metoda spouštějící aplikaci. 
    - **Test třídy**:  
        - Třída CollectorsTest pro testování třídy Collectors.  
        - Třída SettersTest pro testování třídy Setters.  
        - Třída ActionsTest pro testování třídy Actions.   
    - **Diagram tříd: **      
      ![ClassDiagram](uploads/b15056da07779b28eecf44aeafb2376f/ClassDiagram.png)                
- **Dokumentace pro hráče:**  
   - Menu:  
     - tlačítko PLAY - po stisknutí se hra spustí.   
     - tačítlo EXIT - po stisknutí se hra ukončí.   
     - také je možné zapnout nebo vypnout logování v pravém dolním rohu.   
   - Hráč hraje za hlavní postavu(Knight), na obrazovce se zobrazuje úroveň 
     žízně(ve formě vody v pravém horním rohu), úroveň zdraví(ve formě srdce v pravém horním rohu), 
     úroveň obrany(ve formě štítů v pravém horním rohu).  
   - Pohyb probíhá pomocí tlačítek WASD.    
   - Otevření/uzavření inventáře a craftu probíhá pomocí tlačítka R.  
   - Sbírání předmětů probíhá pomocí tlačítka E.    
   - Stisknutím levého tlačítka myši je možné udělat hit.  
   - Stisknutím pravého tlačítka myši je možné si něco vzít z inventáře nebo vyrobit nějaký předmět.  
   - Stisknutím tlačítka ESCAPE je možné přejít do menu a hra skončí.       
   - Hráč má možnost získat materiály(dřevo, kámen), ze kterých může vyrábět zbraně:  
     štít, meč, sekera.  
     Tabulka pro craft:   
     | Typ zbraně(vlastnost)                   | Materiály pro craft |                    
     | --------------------------------------- | ------------------- |                    
     | dřevená sekera(poškození materiálů: 1)  | 2 dřeva             |       
     | dřevený meč(poškození nepřátel: 2)      | 3 dřeva             |       
     | dřevený štít(ochrana: 1)                | 4 dřeva             |       
     | železná sekera(poškození materiálů: 5)  | 1 železo, 1 dřevo   |              
     | železný meč(poškození nepřátel: 6)      | 2 železa, 1 dřevo   |              
     | železný štít(ochrana: 3)                | 3 železa, 1 dřevo   |              
     | kamenná sekera(poškození materiálů: 10) | 1 kámen, 1 dřevo    |               
     | kamenný meč(poškození nepřátel: 10)     | 2 kameny, 1 dřevo   |         
     | kamnný štít(ochrana: 5)                 | 3 kameny, 1 dřevo   |                 
   
   - Hráč má možnost najít komponenty pro jídlo(jablka, pšenice, maso, vodu) pro zvýšení úrovně zdraví 
     a žízně.   
     Tabulka pro craft:    
     | Typ jídla(vlastnost)    | Komponenty pro craft         |                    
     | ----------------------- | ---------------------------- |                    
     | jablko(+1HP)            |                              |       
     | voda(+1 k úrovni žízně) |                              |       
     | koláč(+3HP)             | 2 jablka, 2 vody a 2 pšenice |         
     | polévka(+5HP)           | 3 vody a 1 maso              |                    
     
   - Hra má tři úrovně:  
      1) Pole:
        - první level(bezpečný), hráč může získat jablka, vodu, dřevo a pšenici pro start hry;
        - z nich si musí vyrobit startovní sadu zbraní a trochu jídla, aby se mu otevřel druhý 
          level(druhá úroveň se otevírá, když se v inventáři objeví dřevěná sekera, meč a štít).  
      2) Les:
        - druhý level, na kterém se hráč setká s dívokými obyvateli lesa;
        - po bitvě s nimi bude mít možnost získat ještě sílnější zbraně(najít nové 
          materialy) a maso.  
  - Způsoby zemřít:  
      1) Při boji s nepřítelem(dojde-li ukazatel zdraví);
      2) Kvůli žízni(dojde-li ukazatel hladu).    
            
