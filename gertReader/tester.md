# Chapter 3 oponer
(set: $knowsEnginer to false)
The questions are over. A collective sigh of relief hangs in the air.  Everyone returns to eating slowly and quietly.  The silence is cut by the lurch of the ship going to a sudden stop.
Leah eyes snap to you and she says "Seems the engine has shut off forward momentum. Kaleb why don't you go fix it?".  A small smile graces her face.
[[Why me?|ch3SupGain]]
[[On It boss?|ch3ReactorPuzzle]]
[[Probably the fan belt. It is always the fan belt |ch3FanBelt]]
(if: $knowsEnginer is true)[[I'll give it all she's got captain.|ch3ReactorPuzzle]]

# ch3SupGain
Leah says "Why would I ask you?"
[[I Dont Know| Ch3NotKelab]]
[[Because I work with the engine?|ch3ReactorPuzzle]]
(if: $knowsEnginer is true) [[I am just joking. I am the best engineer y'all could afford.|ch3ReactorPuzzle]]
(if: $knowsEnginer is true) [[Sorry, on it.|ch3ReactorPuzzle]]

# ch3ReactorPuzzle
In the Engine Room, a massive Reactor sits humming with vacuum tubes ablaze with oddly colored lights.
Leah pulls out her holstered gun and says "This is a Flame West revolver, given to me... its old. It will still but a lethal plasma-shell into you." She sighs "I do not want to fire this in this room, I do not want to fire this at all" She drinks from a flask.
Leah Keeping the gun trained on you "So, show me how the reactor works."
[[Sure, come over here, hold this heavy metal plate... please. |ReactorDial1]]
(If: $knowsEnginer) [[Actually this is pretty complicated, I am going to need space.|ReactorDial0]]

# ch3FanBelt
Adrelia Says "The engine has fan belts? I thought it was a fusion reactor."
Leah states "yes why would the reactor need fan belts?"
Rekesh interjects "Why would I know? I am not the engineer, Kal...."
The death stare Leah shoots Rekesh could kill a medium-sized horse. (set: $knowsEnginer to true)
[[It is allways the fan belt.|ch3ReactorPuzzle]]
[[Does fusion mean gassoline?| Ch3NotKelab]]

# Ch3NotKelab
Leah states "that's not Kaleb and fires a round into your skull."
As your body hits the floor you hear a voice say "Let's try again"
[[Chapter 3 oponer]]

# ReactorDial1
While leah is distracted with the heavy object you know you have time to possess someone else. not alot of time.
[[Possess new man | MarvToRek]]
[[Possess Rekesh | RekToMarv]]
[[Work on Reactor | ReactorWork]]

# ReactorDial0
Leah walks all the way to the back of the room.  She is still watching you and that gun is a concern. You see out of a window Rakesh talking to Ardelia holding a rock.
[[Possess new man | MarvToRek]]
[[Possess Rekesh | RekToMarv]]
[[Possess Leah | LeahPossess]]
[[Work on Reactor | ReactorWork]]

# MarvToRek
You see with the Ardelia's eyes. You see Rekesh holding a key card  You see his thoughts he is a geologist named Marv. (set: $MarvID to true)
Rekesh looks at you puzzled and says "Why did you stop talking, these rocks are profitable for business, explain more"
[[ Uh... Sorry had a weird thought| MarvToRek2.1]]
[[ hey is that a keys card? | MarvToRek2.Key]]
(If: $MarvRoom = true) [[[Oh Sorry was thinking of my many sisters| MarvToRek2.2]]]
(If: $MarvRoom = true) [[[The mineral analysis does show promising rare earth element deposits. So that key card is for me? | MarvToRek2.Key]]]

# RekToMarv
Marv continues to discuss the various rocks and readings they found on the moon. untill he posses and says "Wait you stopped me for something what was it?" You look down and see the master key in your hand.
[[ oh I just wanted to tell you I am going to be patrolling the halls|ExploreTime]]
(If: $RekRoom = true)[[(set: $tension = $tension - 1) Oh the business is having great profitable turn over so you can afford that new geological pulse reader |ExploreTime]]
(If: $MarvRoom = true)[[[(set: $tension = $tension - 1)Rock puns |ExploreTime]]]

# LeahPossess
You see through Leah's eyes. you hear her thoughts unraveling a secret.
(set: $LeahSecret to true)
[[head outside |OutsideLeah]]
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
(If: $RekRoom = true)[[(set: $tension = $tension - 1)That memo you sent was really great about how all birthdays should be consolidated into one date. | MarvToRek2.3]]
(If: $MarvRoom = true) [[[Oh the obsidian formation on that moon seem to be caused by heat but their should't be any volcano's. | MarvToRek2.4]]]
(If: $RekRoom = true)[[(set: $tension = $tension - 1)You know the org chart states that I should be holding the master key? | MarvToRek2.Key]]
(If: $MarvRoom = true) [[[Don't expect perfection from Scientist we all have ellectric personalities. Is that a key? | MarvToRek2.Key]]]

# MarvToRek2.Key
(set: $toldAboutKey to true)
Rekesh looks at you for a moment then says "Oh yes it is. I was supposed to give this to you.  The master Key goes to the person with most corporate achievement points. You do beat me every year." He sighs.
I do not think the company knows best this time."
[[Thanks I will patrol the ship |ExploreTime]]
[[Wait do not be so hasty| TryGetKey]]
[[Isnt the corporation where our trust should be?| TryGetKeyG]]

# MarvToRek2.2
Rekesh seems not to know what to say.  He opens his mouth to say something and thinks better of it. Awkward silence is broken by him saying "Yes children"
[[Oh it is nothing, now is that a key card? | MarvToRek2.Key]]
(If: $RekRoom = true)[[(set: $tension = $tension - 1)That memo you sent was really great about how all birthdays should be consolidated into one date. | MarvToRek2.3]]
(If: $MarvRoom = true) [[[Oh the obsidian formation on that moon seem to be caused by heat but there shouldn't be any volcanoes. | MarvToRek2.4]]]
(If: $RekRoom = true)[[(set: $tension = $tension = 1)You know the org chart states that I should be holding the master key? | MarvToRek2.Key]]
(If: $MarvRoom = true) [[[Don't expect perfection from Geologist we all have faults. Is that a key? | MarvToRek2.Key]]]

# MarvToRek2.3
(set: $toldAboutKey to true)
(set: $Marv23 to true)
Rekesh perks up and says "Oh I am glad you enjoyed it. It will save the company 14 cents every year on cards and cake. The cake budget haunts me to this day. But I stopped you for a reason. This is the Master key to all the rooms. I need you to hold onto it."
(If: ($MarvRoom = true and $Marv24 = false)) [[[(set: $tension = $tension - 1)Oh that reminds me of the obsidian formation on that moon seem to be caused by heat but there shouldn't be any volcanoes. | MarvToRek2.4]]]
[[Thanks mate |ExploreTime]]

# MarvToRek2.4
(set: $toldAboutKey to true)
(set: $Marv24 to true)
Rekesh looks perplexed "That is interesting, I know glass sales are always solid. Better than gold. We might be able to corner the artisanal window market. But I stopped you for a reason. This is the Master key to all the rooms. I need you to hold onto it."
(If: ($MarvRoom = true and $Marv23 = false))[[(set: $tension = $tension - 1) Oh that reminds me, That memo you sent was really great about how all birthdays should be consolidated into one date. | MarvToRek2.3]]
[[Thanks mate |ExploreTime]]

# ExploreTime
You have the keycard time to snoop some peoples rooms.
[[tensionLock]]

# TryGetKey
Rekesh looks at you and says "Okay what have I not considered? I know I am me but how do I know you are you?

(If: $RekRoom = true)[[(set: $tension = $tension - 1)You drop a truth bomb on the man. | TryGetKeyG]]
(If: $MarvRoom = true) [[[Have my reports changed any? kaleb is currently doing what he could do in his sleep | TryGetKeyG]]]
(If: $LeahRoom = true)[[(set: $tension = $tension - 1)Look I do trust you, unlike Leah I know you have us all at heart. | TryGetKeyG]]
(If: $MarvRoom = true) [[[(set: $tension = $tension - 1)I know we are all rocked by this but I am me.  | TryGetKeyG]]]
[[(set: $tension = $tension + 3)I got nothing|LeahNotices]]

# TryGetKeyG
Rekesh Says "I am sorry for doubting you. Here take the key I am gonna lie down in my room"
[[Thanks I will patrol the ship |ExploreTime]]

# LeahNotices
Leah shakes you back to your body. The voice in your head louder than ever is hissing.
Leah says "what are you doing? You are not Kaleb!"
Leah vents the room and you slowly suffocate to death.
[[Chapter 3 oponer]]

# OutsideLeah
You see Ardelia talking to Rekesh.
[[Walk over and talk |LeahToRekMarv]]
[[Explore as Leah |LeahExplore]]

# LeahToRekMarv
They both stop talking in shock. Rekesh says "I thought you said you would watch him untill the job is done? what happened?
[[ I trust him.|LeahRekMarv2]]
[[ hey is that a keys card? |LeahMarvRek2.Key]]
(If: $MarvRoom = true) [[[He is doing boring science stuff and i needed to stretch my legs |LeahRekMarv2]]]
(If: $RekRoom = true) [[[Rekesh With Marv's passing I just wanted to apologize for how I have treated you Rekash.|LeahMarvRek2.Key]]]

# LeahExplore
You only have access to leah's room and other shared spaces.
[[Walk over and talk |LeahToRekMarv]]
[[tensionLock]]

# LeahRekMarv2
They stair at you wondering. Rekesh says well Ardelia should have the key her metrix are flawless.
(If: $RekRoom = true)[[(set: $tension = $tension - 1)You drop a truth bomb on the man. |TryGetKeyGLeah]]
(If: $LeahRoom = true)[[(set: $tension = $tension - 1)Look I do trust you, I know i do not show it but I do. |TryGetKeyGLeah]]
(If: $MarvRoom = true) [[[(set: $tension = $tension - 1)I know we are all rocked by this but I should have the key.  |TryGetKeyGLeah]]]
[[(set: $tension = $tension + 3)I got nothing|LeahNotices2]]

# LeahMarvRek2.Key
Rekesh looks at you and says "this keycard is the master key card. I was about to hand it over to Ardelia."
(If: $RekRoom = true)[[(set: $tension = $tension - 1)You drop a truth bomb on the man. |TryGetKeyGLeah]]
(If: $LeahRoom = true)[[(set: $tension = $tension - 1)Look I do trust you, I know i do not show it but I do. |TryGetKeyGLeah]]
(If: $MarvRoom = true) [[[(set: $tension = $tension - 1)I know we are all rocked by this but I am me.  |TryGetKeyGLeah]]]
[[(set: $tension = $tension + 3)I got nothing|LeahNotices2]]

# TryGetKeyGLeah
YOu have the gun and the key the power is all yours!
[[tensionLock]]

# LeahNotices2
You snap to your body and hear shouting in the distance before you know it Leah burst in gun drawn.
[[ What happens next? | Ch3NotKelab]]

# tensionLock
End so far.

# Chapter 1: Start
You find yourself in an airlock with 3 figures watching you.

[[Continue |Opening debate]]

# End of Chapter 1
TThe doors of the airlock open. Ardelia covers her mouth, Rakesh crosses his arms, and Leah steps forward.

As the screen fades to black, you hear the voice: [["We begin, when they end."|Chapter 2]]

# Ms. Information
The three figures look quizically then one shed's a tear and softly says "It's not Kaleb"
The tallest of the three presses the eject button and you are sent on your way

(set: $your_name to true)
[[Drift into space]]

# Drift into space
Rakesh: He must be sick.
Ardelia: Please, there has to be another way.
Rakesh: Quarantine procedures are clear. {delay: 10} Leah.
Leah: I'm sorry, Gabe.

[[Leah blasts you from the airlock. |The Voice]]


# Chapter 2
You eat dinner "with" the three others onboard, Sad and alone in your cell, though you get a great view of the figurative family eating in strokes of glee and worry.

Suddenly you feel sick, a voice roars and rumbles the ship; with no reaction from the crew.

Once your sickness subsides you feel detached and now see an aura from each member of this crew, you're closer to them somehow and feel you will get closer very soon.

Pick a possesion target.

[[ Possess the tallest|ch2pl]]
[[ Possess Mr. white coat|ch2pr]]
[[ Possess the young woman|ch2pa]]

# ch2pr
(if: $rakesh_name is true) [ You find yourself through the eyes of Rakesh. ]
(else:) [ Forced into this man's mind and pristine white coat you now see through their eyes. ]

At nearly the same time, by pure coincidence the tallest turns to you, the white coat, and states "If something is wrong with Kaleb he'd still know his name, this proves nothing! If it's really Kaleb in there he'd know the ships name, your name, my name, Ardelia's name, and our every routine."
(set: $ardelia_name to true)

You, in the white coat, can only sit and stare at this lanky woman, to which she pouts and withdraws herself from your presence. The other, assumed "Adrelia" mutters "I still think it's him, or at worst just feeling real ill."

Though you don't reply it doesn't seem Adrelia wanted or needed a reply, you're a good target to vent to, given the circumstances.

With a little more akward silence and staring you are pulled back into your original body, Kaleb.

[[return|ch2testp1]]

# ch2pl
(if: $leah_name is true) [ You're transported inside the great pilot Leah's mind, ] (else:) [ You merely blink and find yourself through a new view, ] if only you were actually this tall.

Everyone soaks in silence for a short while until (if: $rakesh_name is true) [Rakesh] (else:) [the white coat] interrupts the beautiful nothing with "Leah, we're not against you," and with more courage states "We just don't want to jump to conclusions."
(set: $leah_name to true)

He's looking right at you, and your looking right back. He quickly looks away, clearly terrified of the eye contact.

(if: $ardelia_name is true) [Ardelia] (else:) [The third] blurts out "It's not a trial, rakesh."
(set: $rakesh_name to true)

Rakesh grimmaces but says nothing in return. Tension is high and you want to sneak away from this feels fest, and by pure coincidence you are pulled back to your original body.

[[retreat|ch2testp1]]

# ch2pa
(if: $ardelia_name is true) [ You brain blast your way into Adrelia's mind. ]
(else:) [ You've melded minds with a member of the crew, short (relatively) and colourful. ]

Hearing the other two members arguing certainly annoys you, though why not eavesdrop a little?

The tallest states as immutible fact "If something is wrong with Kaleb he'd still know his name, this proves nothing! If it's really Kaleb in there he'd know the ships name, your name, my name, Ardelia's name, and our every routine."
(set: $ardelia_name to true)

This certainly puts Kaleb in the hot seat, luckily we're not quite him right now and luckily (if: $rakesh_name) [Rakesh] (else:) [the white coat] retorts "As if, you don't announce 'Welcome to a bright new day aboard the Kairos-3 This is your captain speaking-'"
(set: $ship_name to true)

But the tallest cuts him off brandishing her teeth, and as yellow as they may be this certainly scares everyone, and by pure coincidence you're pulled back to your original body.

[[withdraw|ch2testp1]]

# ch2testp1
You're approached by the three crew members, the tallest leads with "Kaleb, we've decided we need more information from you, to see if you are still yourself." With a deep breath she continues "If you fail this test I have no choice but to eject you from this ship, as is procedure."

Everyone looks away breifly as (if: $leah_name is true) [Leah] (else:) [the tallest] begins to question, "What is my name?" she asks.

[[Margret|ch2testdie]]
[[Chad|ch2testdie]]
[[It's my right to remain silent|ch2testdie]]
(if: $leah_name is true) [[Leah|ch2testp2]]

# ch2testdie
(if: $leah_name) [Leah] (else:) [The tallest] is quick to slam the eject button. The airlock bay fails to open. Sadly they have to foresight to press the button a second time and now your in space, dying.

[[Chapter 2]]

# ch2testp2
With some relief from the others Leah presses on.

"Who is this beside me?" She points to the younger woman on her left, your right.

[[Kaleb|ch2testdie]]
[[Mary|ch2testdie]]
[[Arduino|ch2testdie]]
(if: $ardelia_name is true) [[Ardelia|ch2testp3]]

# ch2testp3
Adrelia smiles. Leah puts on her thinking scowl and breaths in.

"What ship are we on?"

(if: $rakesh_name is true) [Rakesh] (else:) [The white coat] quickly blurts out "He might not know that, we shouldn't-"

Leah rudely interrupts with "Fine, if you don't know the ship's name what's his?"

[[Phone a friend?|ch2testdie]]
[[The Scrapper mk2|ch2testdie]]
[[Randy|ch2testdie]]
(if: $ship_name is true) [[Kairos-3|Ch2testpass]]
(if: $rakesh_name is true) [[Rakesh|Ch2testpass]]

# Test 1-1
Leah: I need you to answer this question.
Leah: What is your name?

(if: $your_name is true) [ [["Gabe." |Complete Test 1-1]] ]
[["..." |Protocol]]

# Protocol
(if: $your_name is false)
[Leah: He doesn't know his own name.]
(else-if: $ship_name is false)
[Rakesh: He doesn't know the ship we're on. This madness must be contained.
Leah: Ardelia, I don't know how that's possible. Unless...]
(else-if: $marv_is_dead is false)
[Leah: How could he not know Gates is dead?
Ardelia: Caleb, Marv is gone. Why are you acting like this?
Rakesh: Because he's not himself anymore. This situation is extremely dangerous.]

[[You've failed. |Drift into space]]

# Test 1-2
Ardelia: Okay. Okay. Gabe. Gabe, do you know where you are? {Timer: 60}

[["The airlock." |A bad joke]]
[["..." |Protocol]]
(if: $ship_name is true)
[ [["The Kairos-3."|Complete Test 1-2]]]

# Opening debate
Ardelia: I don't feel comfortable with this.
Rakesh: It's protocol.
Leah: Quiet. He's awake.



# The Voice
As you drift out into space, you hear a voice...

(if: $your_name is false)
[Voice: To end just as we begin.]

(else-if: $ship_name is false)
[Voice: Perhaps one might learn.

You see the name "Kairos-3" as you drift out from the ship.

Voice: Such frailty.
(set: $ship_name to true)
]

(else-if: $marv_is_dead is false)
[Voice: Perhaps one might see.
Voice: Where do you start and end.
]

[[A rush of blue light and you find yourself back in the airlock. |Opening debate]]

# A bad joke
Rakesh: Is that a joke?
Leah: Awful timing.

[[Ardelia stares at you. |Test 1-2]]

# Complete Test 1-1
Ardelia: See, he knows his name. We're all overreacting.
Rakesh: That doesn't account for the past few days.
Leah: Rakesh is right, Ardelia.

[[Ardelia steps closer to the glass, in her hand is a tablet computer. |Test 1-2]]

# Complete Test 1-2
Ardelia: See, he knows where he is!
Leah: Okay, I think we might need to slow this down.

[[Rakesh shakes his head. |Test 1-3]]

# Another bad joke
Rakesh: Another joke.
Leah: We have to follow protocol, Gabe. Answer the questions.
Ardelia: Quiet! Gabe, please look at me. Focus!

[[Ardelia holds a tablet in her hands as she stares from it, to you. |Test 1-3]]

# Test 1-3
Rakesh: Two correct answers and you both toss protocol aside.
Rakesh: Welsh, please explain your behavior. {Timer: 60}

[["Could you tell me what I've done? |Another bad joke]]
[["..." |Protocol]]
(if: $marv_is_dead is true)
[["Gates is dead." |Complete 1-3]]
[["Marv is gone." |Complete 1-3]]

# Player looks at Ardelia
For 30 seconds, player is able to look into Ardelia's eyes. Can move Ardelia's head as she looks around. If the player looks at their body, they see it sitting, in an almost trance-like state.

Can glance down at tablet with the report on Marvin "Marv" Gates' death. Cause of death: Asphyxiation. (set: $marv_is_dead to true)

The player can overhear--

Leah: What happened?
Rakesh: It appears to be another fog. He may not be entirely lucid.

[[You are sucked back into your body. |Test 1-3]]

# Complete 1-3
Ardelia: See, he's lucid.
Leah: Let's calm down.
(if: leah_paranoia &gt;= 1) [Leah: Though something may still be off.]
Rakesh: I am calm. I'm the only one being calm here.
Ardelia: It must be grief.
Rakesh: He doesn't appear sad.
Leah: When's the last time you saw someone grieving, Rakesh? Or maybe experienced a human emotion?
Rakesh: I can recognize grief. Just like hysteria.
Leah: Fuck off. You smarmy-ass collared fuckwit.
Ardelia: Please, stop.

[[The voice cuts through the chatter: "What must they hear?" |Grief]]

# Grief
[["I am sad." |Grief A]]
[["He's... gone." |Grief B]]


# Grief A
Ardelia: See? He's grieving.
Leah: I guess.
Ardelia: Leah, we could be making a huge mistake.
Rakesh: Leah, you must respect protocol. {Wait: 10}
Leah: I'm not convinced.
Leah: We still don't fully understand what's going on.

[[Leah steps forward and punches in a code for the airlock. |End of Chapter 1]]

# Grief B
Ardelia: See? He's grieving.
Leah: Rakesh, I'm not sure.
Rakesh: The decision falls to you.
Leah: We still don't fully understand what's going on.

[[Leah steps forward and punches in a code for the airlock. |End of Chapter 1]]

# Ch2testpass
[[Chapter 3 oponer]]
