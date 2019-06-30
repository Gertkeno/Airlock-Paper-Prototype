# Chapter 3 oponer
A few days hace past and the crew have yet to let you return to work.  Everyone is still on edge but the tension in the ship is loosening its grip as you head towards Dorado 51.
You are awaken by the Voice "Prepare yourself today shall be taxing."
You are thrown from bed by the lurch of the ship going to a sudden stop.
Peyton runs into your room.  Holding a strange keycard. You note this as odd as the rooms have a biometric scan to keep people out of eachother's rooms. "Seems the engine has shut off forward momentum. Gabe why don't you go fix it?".

// added unset function so you can toggle these off/on on respawn situations
// everything is false by default

(UNSET: $paranoia)
(unset: $highTension)
[[On It boss?|ch3ReactorPuzzle]]
[[Probably the fan belt. It is always the fan belt |ch3FanBelt]]
(IF: $knowsEnginer)[[I'll give it all she's got captain. | ch3ReactorPuzzle ]]

# ch3SupGain
Peyton says "Why would I ask you?"
[[I Dont Know | Ch3NotKelab]]
[[Because I work with the engine? | ch3ReactorPuzzle]]
(if: $knowsEnginer) [[I am just joking. I am the best engineer y'all could afford.|ch3ReactorPuzzle]]
(if: $knowsEnginer) [[Sorry, on it. | ch3ReactorPuzzle]]

# ch3ReactorPuzzle
In the Engine Room, a massive Reactor sits silent with many vacuum tubes dimly lighting the room with oddly colored lights.
Peyton pulls out her holstered gun and says "This is a Flame West revolver, given to me... its old. It will still put a lethal plasma-shell into you." She sighs "I do not want to fire this in this room, I do not want to fire this at all" She drinks from a flask.
(if: $paranoia) [Leah Keeping the gun trained on you "So, show me how the reactor works."]
(else:) [Leah holsters the weapon "I am sorry. Could you show me how the reactor works?"]

[[Sure, come over here, hold this heavy metal plate... please. | ReactorDial1]]
(If: $knowsEnginer) [[Actually this is pretty dangerious, I am going to need space. | ReactorDial0]]

# ch3FanBelt
While walking past Esme over hearing says "The engine has fan belts? I thought it was a fusion reactor."
Peyton states "yes why would the reactor need fan belts?"
Esme interjects "Why would I know? I am not the engineer, Gabe..."
The death stare Peyton shoots Esme could kill a medium-sized horse.
(set: $knowsEnginer)
(set: $paranoia)
[[It is allways the fan belt. | ch3ReactorPuzzle]]
[[Does fusion mean gassoline? | Ch3NotKelab]]

# Ch3NotKelab
Peyton states "that's not Kaleb and fires a round into your skull."
As your body hits the floor you hear the Voice say "Let's try again"
[[Chapter 3 oponer]]

# ReactorDial1
While Peyton is distracted with the heavy object you know you have time to possess someone else. not alot of time. You see Rakesh talking to Esme.
[[Possess Esme | MarvToRek]]
[[Possess Rakesh | RekToMarv]]
[[Work on Reactor | ReactorWork]]

# ReactorDial0
Leah walks all the way to the back of the room.  She is still watching you and that gun is a concern. You see out of a window Rakesh talking to Esme holding a rock.
[[Possess Esme | MarvToRek]]
[[Possess Rakesh | RekToMarv]]
[[Possess Peyton | LeahPossess]]
[[Work on Reactor | ReactorWork]]

# MarvToRek
You see with the Ardelia's eyes. You see Rekesh holding a key card  You see his thoughts he is a geologist named Marv.
(set: $MarvID)
Rekesh looks at you puzzled and says "Why did you stop talking, these rocks are profitable for business, explain more"
[[ Uh... Sorry had a weird thought| MarvToRek2.1]]
[[ hey is that a keys card? | MarvToRek2.Key]]
(If: $MarvRoom) [[Oh Sorry was thinking of my many sisters | MarvToRek2.2]]
(If: $MarvRoom) [[The mineral analysis does show promising rare earth element deposits. So that key card is for me? | MarvToRek2.Key]]

# RekToMarv
Marv continues to discuss the various rocks and readings they found on the moon. untill he posses and says "Wait you stopped me for something what was it?" You look down and see the master key in your hand.

[[oh I just wanted to tell you I am going to be patrolling the halls | ExploreTime]]
(If: $RekRoom)     [[Oh the business is having great profitable turn over so you can afford that new geological pulse reader | ExploreTime]]
(If: $MarvRoom)    [[Rock puns | ExploreTime]]

# LeahPossess
You see through Leah's eyes. you hear her thoughts unraveling a secret.
(set: $LeahSecret)
[[head outside | OutsideLeah]]
[[Shoot reactor| ReactorExplodes]]

# ReactorWork
[[Try the Blue bulb| ReactorOverHeats]]

# ReactorOverHeats
[[Try the Red Bulb | ReactorExplodes]]

# ReactorExplodes
A voice in your head chuckles.
[[Chapter 3 oponer]]

# MarvToRek2.1
Rekesh says "weird thoughts like what? are you feeling okay you seemed a little shook all of the sudden."
[[Oh it is nothing, now is that a key card? | MarvToRek2.Key]]
(If: $RekRoom)  [[That memo you sent was really great about how all birthdays should be consolidated into one date. | MarvToRek2.3]]
(If: $MarvRoom) [[Oh the obsidian formation on that moon seem to be caused by heat but their should't be any volcano's. | MarvToRek2.4]]
(If: $RekRoom)  [[You know the org chart states that I should be holding the master key? | MarvToRek2.Key]]
(If: $MarvRoom) [[Don't expect perfection from Scientist we all have ellectric personalities. Is that a key? | MarvToRek2.Key]]

# MarvToRek2.Key
(set: $toldAboutKey)
Rekesh looks at you for a moment then says "Oh yes it is. I was supposed to give this to you.  The master Key goes to the person with most corporate achievement points. You do beat me every year." He sighs.
(if: $highTension) ["I do not think the company knows best this time.]
(else:) ["I feel like you are the only one I can trust. The company metrics are clearly right to trust you." ]

(if: $highTension) [[Wait do not be so hasty| TryGetKey]]
(else:) [[Thanks I will patrol the ship |ExploreTime]]

(if: $RekRoom) [[Isnt the corporation where our trust should be?| TryGetKeyG]]

# MarvToRek2.2
(set: $highTension)
Rekesh seems not to know what to say.  He opens his mouth to say something and thinks better of it. Awkward silence is broken by him saying "Yes children"
[[Oh it is nothing, now is that a key card? | MarvToRek2.Key]]

(If: $RekRoom)  [[That memo you sent was really great about how all birthdays should be consolidated into one date. | MarvToRek2.3]]
(If: $MarvRoom) [[Oh the obsidian formation on that moon seem to be caused by heat but there shouldn't be any volcanoes. | MarvToRek2.4]]
(If: $RekRoom)  [[You know the org chart states that I should be holding the master key? | MarvToRek2.Key]]
(If: $MarvRoom) [[Don't expect perfection from Geologist we all have faults. Is that a key? | MarvToRek2.Key]]

# MarvToRek2.3
(set: $toldAboutKey)
(set: $Marv23)
Rekesh perks up and says "Oh I am glad you enjoyed it. It will save the company 14 cents every year on cards and cake. The cake budget haunts me to this day. But I stopped you for a reason. This is the Master key to all the rooms. I need you to hold onto it."
(If: $MarvRoom) (else:) (and: $Marv24) [[Oh that reminds me of the obsidian formation on that moon seem to be caused by heat but there shouldn't be any volcanoes. | MarvToRek2.4]]
[[Thanks mate | ExploreTime]]

# MarvToRek2.4
(set: $toldAboutKey)
(set: $Marv24)
Rekesh looks perplexed "That is interesting, I know glass sales are always solid. Better than gold. We might be able to corner the artisanal window market. But I stopped you for a reason. This is the Master key to all the rooms. I need you to hold onto it."
(If: $MarvRoom) (else:) (and: $Marv23) [[ Oh that reminds me, That memo you sent was really great about how all birthdays should be consolidated into one date. | MarvToRek2.3]]
[[Thanks mate |ExploreTime]]

# ExploreTime
You have the keycard time to snoop some peoples rooms.
[[tensionLock]]

# TryGetKey
Rekesh looks at you and says "Okay what have I not considered? I know I am me but how do I know you are you?

(If: $RekRoom)  [[You drop a truth bomb on the man. | TryGetKeyG]]
(If: $MarvRoom) [[Have my reports changed any? kaleb is currently doing what he could do in his sleep | TryGetKeyG]]
(If: $LeahRoom) [[Look I do trust you, unlike Leah I know you have us all at heart. | TryGetKeyG]]
(If: $MarvRoom) [[I know we are all rocked by this but I am me. | TryGetKeyG]]
[[I got nothing | LeahNotices]]

# TryGetKeyG
Rekesh Says "I am sorry for doubting you. Here take the key I am gonna lie down in my room"
[[Thanks I will patrol the ship | ExploreTime]]

#LeahNotices
Leah shakes you back to your body. The voice in your head louder than ever is hissing.
Leah says "what are you doing? You are not Kaleb!"
Leah vents the room and you slowly suffocate to death.
[[Chapter 3 oponer]]

#OutsideLeah
You see Ardelia talking to Rekesh.
[[Walk over and talk | LeahToRekMarv]]
[[Explore as Leah |LeahExplore]]

#LeahToRekMarv
They both stop talking in shock. Rekesh says "I thought you said you would watch him untill the job is done? what happened?
[[I trust him. | LeahRekMarv2]]
[[hey is that a keys card? | LeahMarvRek2.Key]]
(If: $MarvRoom) [[He is doing boring science stuff and i needed to stretch my legs | LeahRekMarv2]]
(If: $RekRoom) [[Rekesh With Marv's passing I just wanted to apologize for how I have treated you Rekash. | LeahMarvRek2.Key]]

#LeahExplore
You only have access to leah's room and other shared spaces.
[[Walk over and talk |LeahToRekMarv]]
[[tensionLock]]

#LeahRekMarv2
They stair at you wondering. Rekesh says well Ardelia should have the key her metrix are flawless.
(If: $RekRoom)  [[You drop a truth bomb on the man. |TryGetKeyGLeah]]
(If: $LeahRoom) [[Look I do trust you, I know i do not show it but I do. |TryGetKeyGLeah]]
(If: $MarvRoom) [[I know we are all rocked by this but I should have the key.  |TryGetKeyGLeah]]
[[I got nothing|LeahNotices2]]

#LeahMarvRek2.Key
Rekesh looks at you and says "this keycard is the master key card. I was about to hand it over to Ardelia."
(If: $RekRoom)  [[You drop a truth bomb on the man. |TryGetKeyGLeah]]
(If: $LeahRoom) [[Look I do trust you, I know i do not show it but I do. |TryGetKeyGLeah]]
(If: $MarvRoom) [[I know we are all rocked by this but I am me.  |TryGetKeyGLeah]]
[[I got nothing|LeahNotices2]]

#TryGetKeyGLeah
YOu have the gun and the key the power is all yours!
[[tensionLock]]

#LeahNotices2
You snap to your body and hear shouting in the distance before you know it Leah burst in gun drawn.
[[ What happens next? | Ch3NotKelab]]

#tensionLock
End so far.

//#Chapter 1: Start
//Chapter 3 starts!
//
//[[GO to Chapter 3 |Chapter 3 oponer]]
//(set: $MarvID to false)
//(set: $MarvRoom to false)
//(set: $RekRoom to false)
//(set: $LeahRoom to false)
//(set: $AidRoom to false)
//(set: $toldAboutKey to false)
//(set: $Marv23 to false)
//(set: $marv24 to false)
//(set: $LeahSecret to false)
//(set: $knowsKeyCard to "strange key card")
//(set: $textChoice1 = "")
//(set: $textChoice2 = "")
//(set: $textChoice3 = "")
//(set: $textChoice4 = "")
//(set: $textWords1 = "")
//(set: $textWords2 = "")
//(set: $textWords3 = "")
//(set: $textWords4 = "")
//(set: $youNameF = "Gabriel")
//(set: Gabe = "Gabe")
//(set: Peyton = "Peyton")
//(set: Esme = "Esme")
//(set: Rakesh = "Rekesh")
//(set: $deadNameF = "Marvin")
//(set: $deadNameN = "Marv")
//(set: $deadNameN = "Andras")
//(set: $shipName = "Karn 1369")
//(set: Dorado 51 = "Dorado 51")
//(set: $deathCounter = 0)

//#how Write CHoices
//text
//[[choice to raise paranoia |]]
//(set: $textChoice1 = "event3")(set: $textWords1 = "choice to raise paranoia")
//[[choice to lower paranoia | ]]
//(set: $textChoice2 = "")(set: $textWords2 = "choice to lower paranoia")
//
//#ParaPlus
//(set: $paranoia = $paranoia + 1)
//(click: ?$textWords1)[(goto:$textChoice1)]
//
//
//#ParaMinus
//(set: $paranoia = $paranoia - 1)
//(click: ?$textWords1)[(goto:$textChoice1)]
//
//
//#ParaPlus2
//(set: $paranoia = $paranoia + 1)
//(click: ?$textWords2)[(goto:$textChoice2)]
//
//#ParaMinus2
//(set: $paranoia = $paranoia - 1)
//(click: ?$textWords2)[(goto:$textChoice2)]
//
//
//#ParaPlus3
//(set: $paranoia = $paranoia + 1)
//(click: ?$textWords3)[(goto:$textChoice3)]
//
//
//#ParaMinus3
//(set: $paranoia = $paranoia - 1)
//(click: ?$textWords3)[(goto:$textChoice3)]
