# Jord'simulator' TDT4102 Prosjekt Vår 26 
<br>

Programmet skulle være en simulering av jorda, men jeg kom ikke helt i mål. Det er nå en veldig enkel globus / flysimulator.

Jeg bruker Animationwindow med projiseringsmattematikk og velkjente transformeringsformler for å rendre 3d-objekter.
Programmet skaper så jorda og solen etter brukerens ønske og leser inn et bilde av overflaten som den mapper til disse kulene. Flydataene er hentet fra openSky (?) og var real-time da jeg hentet de. Programmet går igjennom filen, skaper et fly-objekt for hvert fly og tegner de riktig posisjonert på jordoverflaten. 

Når man går inn i et fly, byttes "kameraet" til fly-kameraobjektet, slik at man kan gå tilbake til det originale kameraet når som helst.

## Utviklingsprosessen

Jeg startet tidlig med å utlede matten bak projisering, rotasjon, forflytning og 3d objekter for hånd. Mesteparten ligger i filen 'Utregninger.pdf'. Alt er forsøkt å gjøre med intuisjon og matte 2A, men jeg brukte en LLM for å dobbeltsjekke om matten var korrekt. Det stemte som regel. Deretter implementerte jeg det i programmet selv.

Mot slutten brukte jeg mindre tid på mattematikken, slik at jeg fikk mer tid til å faktisk skrive kode. Jeg ga det likevel et forsøk og tok meg tiden til å forstå det.


### KI
Jeg har brukt store språkmodeller (LLM) til mattematikk, som siste utvei i debugging og som et oppslagsverk på syntaks. Jeg brukte den og for å lese gjennom AnimationWindow-koden så den fant ut hvordan jeg kunne bruke SDL-biblioteket til å lese bildene pixel for pixel. All koden i programmet mitt er skrevet av meg.


