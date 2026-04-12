
# JordSim — Dokumentasjon
*TDT4102, NTNU — Vår 2026*

### Utviklingsprosessen

Jeg startet tidlig med å utlede matten bak projisering, rotasjon, forflytning og 3d objekter for hånd. Mesteparten ligger i filen 'Utregninger.pdf'. Alt er forsøkt å gjøre med intuisjon og matte 2A, men jeg brukte en LLM for å dobbeltsjekke om matten var korrekt. Det stemte som regel. Deretter implementerte jeg det i programmet selv.

Mot slutten brukte jeg mindre tid på mattematikken, slik at jeg fikk mer tid til å faktisk skrive kode. Jeg ga det likevel et forsøk og tok meg tiden til å forstå det.
---

## Hva programmet gjør

JordSim er en interaktiv 3D-simulasjon av jorda, sola og flytrafikk. Programmet renderer en tredimensjonal globus med teksturert jordoverflate og sol, og viser posisjoner til reelle fly hentet fra en lokal datafil basert på ADS-B/OpenSky-data. Brukeren kan navigere fritt i rommet med tastaturet og rotere kameraet.

Ved oppstart vises en hovedmeny der brukeren velger hva som skal tegnes (jord, sol, fly) og hvilken geometrisk oppløsning kulen skal ha. Deretter starter simuleringen.

---

## Logikk bak implementasjonen

### 3D-rendering
Prosjektet implementerer en egenutviklet software renderer uten OpenGL eller lignende. Trekanter projiseres fra 3D-verdenskoordinater til 2D-skjermkoordinater via perspektivprojeksjon med et definert focal length. Trekantene sorteres etter dybde (painters algorithm) før tegning for å gi korrekt overlapp.

### Kule-generering
Kulen starter som en kube lest fra en `.obj`-fil. `dobleTrekanter()` subdivider hver trekant i fire mindre trekanter gjentatte ganger. `Spherifiser()` normaliserer deretter alle punkter til ønsket radius, slik at kuben blir en tilnærmet kule. Antall subdivideringer styres av brukeren via slideren i hovedmenyen.

### Teksturering
Kartkoordinater (bredde- og lengdegrad) beregnes fra kartesiske koordinater med `KartesiskTilSpherisk()`. Disse brukes til å slå opp riktig piksel i et innlastet kartbilde, som mappes til hver trekant i `mapBildeTilKule()`.

### Flydata
Flydata leses fra en tekstfil i JSON-lignende format. Hvert fly konverteres fra geografiske koordinater (lat/lon/høyde) til kartesiske 3D-koordinater i `finnKartesisk()`. Flyene beveger seg fremover med `flyFremmover()` og roterer med jorda via `roterMedJord()`.

### Kamera
Kameraet støtter yaw og pitch-rotasjon via Rodrigues' rotasjonsformel og beveger seg i sin egen retning med WASD.


### KI
Jeg har brukt store språkmodeller (LLM) til mattematikk, som siste utvei i debugging og som et oppslagsverk på syntaks. Jeg brukte den og for å lese gjennom AnimationWindow-koden så den fant ut hvordan jeg kunne bruke SDL-biblioteket til å lese bildene pixel for pixel. All koden i programmet mitt er skrevet av meg.

### Eksterne ressurser
- [OpenSky Network](https://opensky-network.org/) — Kilde for ADS-B flydata
-  Kartbilde: NASA Blue Marble