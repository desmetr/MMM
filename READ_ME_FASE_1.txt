READ_ME ALGORITMES FASE 1
--------------------------

Deze READ_ME legt uit welke algoritmes we hebben geïmplementeerd.

1) Jago heeft de CFG klasse en het CYK algoritme geïmplementeerd.

// TODO uitleg over hoe je jouw testen runt.

2) Benoitphilippe heeft het CNF algoritme geïmplementeerd.

// TODO uitleg over je jouw testen runt.

3) Rafael heeft de PDA klasse en het converteren van een PDA die accepteert via accept state
naar een PDA die accepteert via een lege stack.

De source code staat in de folder PDA/src. Hierin staan ook de testen die ikzelf al heb gemaakt.
Om een test te runnen met de naam test.xml moet je oppassen. In de terminal is het de bedoeling om
deze file mee te geven aan het programma. Het programma genereert twee bestanden. Een .dot file en een .png file.
Deze dienen om de PDA te laten zien. Om zeker te zijn dat we onderscheid kunnen maken tussen de verschillende files,
moet je ipv 'test.xml' mee te geven als argument, alleen 'test' meegeven. Het postfix .xml mag dus niet meegegeven worden.
Het programma gaat het meegegeven argument gebruiken om de twee bestanden met de juiste naam aan te maken.
Er worden dus twee nieuwe bestanden aangemaakt, nl. test.dot en test.dot.png (als de input file test.xml heet).

De files examplePDA0.xml, examplePDA1.xml en examplePDA2.xml zijn drie testen die verschillende PDA's voorstellen.
De files examplePDAEmpty0.xml, examplePDAEmpty1.xml en examplePDAEmpty2.xml zijn drie testen voor het eigenlijke conversie algoritme.
