

#include <Blast/TaoTeChingQuoteGenerator.hpp>
#include <algorithm>
#include <iterator>
#include <random>
#include <random>
#include <iostream>


namespace Blast
{


TaoTeChingQuoteGenerator::TaoTeChingQuoteGenerator(std::vector<std::string> quotes)
   : quotes(quotes)
{
}


TaoTeChingQuoteGenerator::~TaoTeChingQuoteGenerator()
{
}


std::string TaoTeChingQuoteGenerator::pick_quote()
{
   if (quotes.empty()) return "";
   std::vector<std::string> result;
   std::sample(quotes.begin(), quotes.end(), std::back_inserter(result), 1, std::mt19937{std::random_device{}()});
   return result[0];
}

std::vector<std::string> TaoTeChingQuoteGenerator::default_quotes_list()
{
   return {
      "The tao that can be told is not the eternal Tao.  The name that can be named is not the eternal name.",
      "The unnamable is the eternally real.  Naming is the origin of all particular things.",
      "Free from desire, you realize the mystery." \
         "Caught in desire, you see only the manifestations.",
      "Yet mystery and manifestations arise from the same source." \
         "This source is called darkness.",
      "Darkness within darkness." \
         "The gateway to all understanding.",
      "The Tao is like a well: used but never used up." \
         "It is like the eternal void: filled with infinite possibilities.",
      "It is hidden but always present." \
         "I don't know who gave birth to it." \
         "It is older than God.",
      "The Tao doesn't take sides; it gives birth to both good and evil." \
         "The Master doesn't take sides; she welcomes both saints and sinners.",
      "The Tao is like a bellows: it is empty yet infinitely capable." \
         "The more you use it, the more it produces; the more you talk of it, the less you understand." \
         "Hold on to the center.",
      "The Tao is infinite, eternal. Why is it eternal? It was never born; thus it can never die." \
         "Why is it infinite? It has no desires for itself; thus it is present for all beings.",
      "The Master stays behind; that is why she is ahead." \
         "She is detached from all things; that is why she is one with them." \
         "Because she has let go of herself, she is perfectly fulfilled.",
      "Success is as dangerous as failure. Hope is as hollow as fear.",
      "What does it mean that success is as dangerous as failure?" \
         "Whether you go up the ladder or down it, your position is shaky." \
         "When you stand with your two feet on the ground, you will always keep your balance.",
      "What does it mean that hope is as hollow as fear?" \
         "Hope and fear are both phantoms that arise from thinking of the self." \
         "When we don't see the self as self, what do we have to fear?",
      "See the world as your self." \
         "Have faith in the way things are." \
         "Love the world as your self;" \
         "then you can care for all things.",
      "Empty your mind of all thoughts." \
         "Let your heart be at peace." \
         "Watch the turmoil of beings, but contemplate their return.",
      "Each separate being in the universe returns to the common source. Returning to the source is serenity.",
      "If you don't realize the source," \
         "you stumble in confusion and sorrow." \
         "When you realize where you come from, you naturally become tolerant," \
         "disinterested, amused, kindhearted as a grandmother, dignified as a king." \
         "Immersed in the wonder of the Tao," \
         "you can deal with whatever life brings you," \
         "and when death comes," \
         "you are ready." \
         "The great Tao flows everywhere",
      "All things are born from it, yet it doesn't create them." \
         "It pours itself into its work, yet it makes no claim." \
         "It nourishes infinite worlds, yet it doesn't hold on to them." \
         "Since it is merged with all things and hidden in their hearts, it can be called humble." \
         "Since all things vanish into it and it alone endures, it can be called great." \
         "It isn't aware of its greatness; thus it is truly great.",
      "The Tao gives birth to One." \
         "One gives birth to Two." \
         "Two gives birth to Three." \
         "Three gives birth to all things.",
      "All things have their backs to the female and stand facing the male." \
         "When male and female combine, all things achieve harmony.",
      "Ordinary men hate solitude." \
         "But the Master makes use of it, embracing his aloneness, realizing he is one with the whole universe.",
      "Whoever is planted in the Tao will not be rooted up." \
         "Whoever embraces the Tao will not slip away." \
         "Her name will be held in honor from generation to generation.",
      "Let the Tao be present in your life and you will become genuine." \
         "Let it be present in your family and your family will flourish." \
         "Let it be present in your country and your country will be an example to all countries in the world." \
         "Let it be present in the universe and the universe will sing.",
      "How do I know this is true?  By looking inside myself.",
      "If you want to be a great leader, you must learn to follow the Tao." \
         "Stop trying to control." \
         "Let go of fixed plans and concepts, and the world will govern itself.",
      "The more prohibitions you have, the less virtuous people will be." \
         "The more weapons you have, the less secure people will be." \
         "The more subsidies you have, the less self-reliant people will be.",
      "Therefore the Master says: I let go of the law, and people become honest." \
         "I let go of economics, and people become prosperous." \
         "I let go of religion and people become serene." \
         "I let go of all desire for the common good, and the good becomes common as grass.",
      "If a country is governed with tolerance, the people are comfortable and honest." \
         "If a country is governed with repression, the people are depressed and crafty.",
      "When the will to power is in charge, the higher the ideals, the lower the results." \
         "Try to make people happy, and you lay the groundwork for misery." \
         "Try to make people moral, and you lay the groundwork for vice.",
      "Thus the Master is content to serve as an example and not to impose her will." \
         "She is pointed, but doesn't pierce." \
         "Straightforward, but supple. Radiant, but easy on the eyes.",
      "If you realize that all things change, there is nothing you will try to hold on to." \
         "If you aren't afraid of dying, there is nothing you can't achieve.",
      "Trying to control the future is like trying to take the master carpenter's place." \
         "When you handle the master carpenter's tools, chances are that you'll cut your hand.",
      "Red is not red.\nBlue is not blue.\nHard is not hard.\nSoft is not soft.\nMale" \
         "is not male.\nFemale is not female.There is just this jazz.\n\n-Alan Watts",
   };
}
} // namespace Blast


