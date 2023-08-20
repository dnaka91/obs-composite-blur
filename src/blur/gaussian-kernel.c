#include <stddef.h>

// Pre-computed center-right symmetric normalized gaussian kernel lookup table.
// kernel[0] is maximum value of the gaussian function. Subsequent values are
// symmetrical value moving out from center in both directions.
const size_t gaussian_kernel_size = 1024;
const float gaussian_kernel[] = {
	0.0011719249766483813f,  0.0011719199473027937f,
	0.0011719048593955318f,  0.0011718797133150934f,
	0.0011718445097089552f,  0.0011717992494835467f,
	0.0011717439338042107f,  0.001171678564095152f,
	0.0011716031420393785f,  0.0011715176695786275f,
	0.0011714221489132822f,  0.0011713165825022786f,
	0.001171200973062999f,   0.0011710753235711557f,
	0.0011709396372606626f,  0.0011707939176234987f,
	0.0011706381684095553f,  0.0011704723936264774f,
	0.001170296597539491f,   0.0011701107846712206f,
	0.0011699149598014943f,  0.00116970912796714f,
	0.0011694932944617692f,  0.0011692674648355493f,
	0.0011690316448949676f,  0.0011687858407025795f,
	0.001168530058576752f,   0.001168264305091391f,
	0.0011679885870756598f,  0.0011677029116136874f,
	0.0011674072860442647f,  0.0011671017179605303f,
	0.0011667862152096454f,  0.0011664607858924588f,
	0.0011661254383631581f,  0.0011657801812289148f,
	0.0011654250233495145f,  0.0011650599738369783f,
	0.0011646850420551735f,  0.0011643002376194131f,
	0.0011639055703960447f,  0.001163501050502029f,
	0.0011630866883045074f,  0.00116266249442036f,
	0.0011622284797157506f,  0.0011617846553056645f,
	0.001161331032553433f,   0.0011608676230702494f,
	0.001160394438714672f,   0.0011599114915921203f,
	0.0011594187940543582f,  0.0011589163586989669f,
	0.0011584041983688086f,  0.0011578823261514791f,
	0.0011573507553787508f,  0.0011568094996260055f,
	0.0011562585727116546f,  0.001155697988696554f,
	0.001155127761883403f,   0.0011545479068161397f,
	0.0011539584382793187f,  0.001153359371297486f,
	0.00115275072113454f,    0.0011521325032930818f,
	0.0011515047335137597f,  0.0011508674277745988f,
	0.001150220602290325f,   0.001149564273511677f,
	0.001148898458124708f,   0.0011482231730500809f,
	0.001147538435442349f,   0.001146844262689232f,
	0.0011461406724108795f,  0.0011454276824591244f,
	0.0011447053109167298f,  0.001143973576096624f,
	0.0011432324965411265f,  0.0011424820910211657f,
	0.0011417223785354857f,  0.0011409533783098458f,
	0.0011401751097962081f,  0.0011393875926719202f,
	0.0011385908468388825f,  0.0011377848924227136f,
	0.0011369697497719004f,  0.001136145439456944f,
	0.0011353119822694936f,  0.0011344693992214722f,
	0.0011336177115441957f,  0.001132756940687479f,
	0.0011318871083187381f,  0.0011310082363220795f,
	0.0011301203467973843f,  0.0011292234620593807f,
	0.0011283176046367103f,  0.0011274027972709858f,
	0.0011264790629158384f,  0.0011255464247359591f,
	0.0011246049061061306f,  0.0011236545306102508f,
	0.0011226953220403492f,  0.0011217273043955943f,
	0.0011207505018812922f,  0.0011197649389078801f,
	0.0011187706400899086f,  0.0011177676302450174f,
	0.0011167559343929047f,  0.0011157355777542857f,
	0.0011147065857498458f,  0.001113668983999187f,
	0.0011126227983197627f,  0.0011115680547258097f,
	0.001110504779427269f,   0.0011094329988287032f,
	0.0011083527395282012f,  0.0011072640283162811f,
	0.0011061668921747822f,  0.0011050613582757516f,
	0.0011039474539803243f,  0.001102825206837593f,
	0.0011016946445834759f,  0.0011005557951395727f,
	0.001099408686612018f,   0.0010982533472903254f,
	0.0010970898056462252f,  0.0010959180903324962f,
	0.0010947382301817914f,  0.0010935502542054555f,
	0.0010923541915923375f,  0.0010911500717075964f,
	0.0010899379240915015f,  0.0010887177784582244f,
	0.0010874896646946273f,  0.0010862536128590436f,
	0.001085009653180053f,   0.001083757816055252f,
	0.001082498132050016f,   0.0010812306318962568f,
	0.0010799553464911757f,  0.0010786723068960092f,
	0.0010773815443347694f,  0.0010760830901929805f,
	0.0010747769760164072f,  0.0010734632335097794f,
	0.001072141894535513f,   0.0010708129911124217f,
	0.0010694765554144275f,  0.0010681326197692638f,
	0.0010667812166571746f,  0.0010654223787096083f,
	0.0010640561387079066f,  0.0010626825295819888f,
	0.0010613015844090324f,  0.0010599133364121468f,
	0.0010585178189590444f,  0.0010571150655607068f,
	0.001055705109870046f,   0.0010542879856805625f,
	0.0010528637269249968f,  0.0010514323676739802f,
	0.0010499939421346781f,  0.0010485484846494318f,
	0.0010470960296943943f,  0.0010456366118781649f,
	0.0010441702659404158f,  0.0010426970267505206f,
	0.0010412169293061737f,  0.00103973000873201f,
	0.0010382363002782182f,  0.0010367358393191543f,
	0.001035228661351948f,   0.0010337148019951075f,
	0.0010321942969871215f,  0.0010306671821850577f,
	0.0010291334935631587f,  0.0010275932672114331f,
	0.0010260465393342464f,  0.0010244933462489072f,
	0.0010229337243842515f,  0.0010213677102792241f,
	0.0010197953405814576f,  0.0010182166520458485f,
	0.0010166316815331312f,  0.00101504046600845f,
	0.0010134430425399281f,  0.001011839448297235f,
	0.0010102297205501513f,  0.0010086138966671325f,
	0.0010069920141138687f,  0.0010053641104518457f,
	0.0010037302233369006f,  0.0010020903905177787f,
	0.0010004446498346872f,  0.0009987930392178481f,
	0.0009971355966860481f,  0.000995472360345189f,
	0.000993803368386837f,   0.0009921286590867673f,
	0.0009904482708035117f,  0.0009887622419769032f,
	0.0009870706111266192f,  0.0009853734168507242f,
	0.0009836706978242126f,  0.0009819624927975478f,
	0.0009802488405952052f,  0.0009785297801142097f,
	0.0009768053503226761f,  0.0009750755902583468f,
	0.0009733405390271314f,  0.0009716002358016431f,
	0.000969854719819737f,   0.0009681040303830478f,
	0.000966348206855527f,   0.0009645872886619795f,
	0.000962821315286602f,   0.0009610503262715194f,
	0.0009592743612153234f,  0.0009574934597716095f,
	0.000955707661647516f,   0.0009539170066022619f,
	0.0009521215344456867f,  0.0009503212850367895f,
	0.00094851629828227f,    0.0009467066141350689f,
	0.0009448922725929095f,  0.0009430733136968416f,
	0.0009412497775297837f,  0.0009394217042150686f,
	0.000937589133914988f,   0.000935752106829341f,
	0.00093391066319398f,    0.0009320648432793618f,
	0.0009302146873890977f,  0.0009283602358585053f,
	0.0009265015290531624f,  0.0009246386073674626f,
	0.0009227715112231713f,  0.0009209002810679854f,
	0.0009190249573740924f,  0.0009171455806367343f,
	0.0009152621913727696f,  0.0009133748301192423f,
	0.0009114835374319471f,  0.0009095883538840019f,
	0.0009076893200644201f,  0.0009057864765766847f,
	0.0009038798640373266f,  0.000901969523074503f,
	0.0009000554943265809f,  0.0008981378184407207f,
	0.0008962165360714644f,  0.0008942916878793248f,
	0.0008923633145293787f,  0.0008904314566898629f,
	0.0008884961550307713f,  0.0008865574502224581f,
	0.0008846153829342409f,  0.0008826699938330087f,
	0.0008807213235818327f,  0.00087876941283858f,
	0.0008768143022545306f,  0.0008748560324729984f,
	0.0008728946441279547f,  0.0008709301778426554f,
	0.0008689626742282725f,  0.0008669921738825287f,
	0.0008650187173883341f,  0.0008630423453124301f,
	0.0008610630982040336f,  0.0008590810165934869f,
	0.0008570961409909112f,  0.0008551085118848646f,
	0.0008531181697410016f,  0.0008511251550007405f,
	0.0008491295080799323f,  0.000847131269367534f,
	0.0008451304792242872f,  0.0008431271779814006f,
	0.0008411214059392359f,  0.0008391132033660001f,
	0.0008371026104964406f,  0.0008350896675305446f,
	0.0008330744146322458f,  0.0008310568919281318f,
	0.0008290371395061594f,  0.0008270151974143735f,
	0.0008249911056596307f,  0.0008229649042063276f,
	0.0008209366329751345f,  0.0008189063318417342f,
	0.0008168740406355652f,  0.000814839799138571f,
	0.0008128036470839525f,  0.0008107656241549283f,
	0.0008087257699834988f,  0.0008066841241492142f,
	0.0008046407261779516f,  0.0008025956155406931f,
	0.0008005488316523128f,  0.0007985004138703676f,
	0.0007964504014938936f,  0.0007943988337622083f,
	0.0007923457498537193f,  0.0007902911888847369f,
	0.0007882351899082933f,  0.0007861777919129689f,
	0.0007841190338217219f,  0.0007820589544907257f,
	0.0007799975927082107f,  0.0007779349871933143f,
	0.0007758711765949339f,  0.0007738061994905889f,
	0.0007717400943852862f,  0.0007696728997103933f,
	0.0007676046538225184f,  0.0007655353950023934f,
	0.0007634651614537675f,  0.0007613939913023033f,
	0.0007593219225944817f,  0.0007572489932965115f,
	0.0007551752412932471f,  0.0007531007043871115f,
	0.0007510254202970245f,  0.0007489494266573413f,
	0.0007468727610167941f,  0.0007447954608374403f,
	0.0007427175634936207f,  0.0007406391062709203f,
	0.0007385601263651386f,  0.0007364806608812652f,
	0.0007344007468324629f,  0.000732320421139057f,
	0.0007302397206275318f,  0.0007281586820295339f,
	0.0007260773419808828f,  0.0007239957370205873f,
	0.0007219139035898697f,  0.0007198318780311974f,
	0.0007177496965873204f,  0.0007156673954003163f,
	0.0007135850105106431f,  0.0007115025778561978f,
	0.0007094201332713832f,  0.0007073377124861815f,
	0.0007052553511252344f,  0.0007031730847069319f,
	0.0007010909486425069f,  0.000699008978235138f,
	0.0006969272086790587f,  0.000694845675058675f,
	0.0006927644123476896f,  0.0006906834554082332f,
	0.0006886028389900044f,  0.0006865225977294153f,
	0.0006844427661487458f,  0.0006823633786553056f,
	0.0006802844695406017f,  0.0006782060729795158f,
	0.0006761282230294877f,  0.0006740509536297064f,
	0.0006719742986003098f,  0.00066989829164159f,
	0.0006678229663332081f,  0.0006657483561334155f,
	0.0006636744943782833f,  0.0006616014142809388f,
	0.0006595291489308107f,  0.0006574577312928801f,
	0.0006553871942069415f,  0.0006533175703868693f,
	0.0006512488924198938f,  0.0006491811927658835f,
	0.0006471145037566362f,  0.0006450488575951768f,
	0.0006429842863550641f,  0.0006409208219797041f,
	0.0006388584962816721f,  0.0006367973409420417f,
	0.0006347373875097224f,  0.0006326786674008041f,
	0.0006306212118979107f,  0.0006285650521495598f,
	0.000626510219169532f,   0.0006244567438362464f,
	0.0006224046568921458f,  0.0006203539889430875f,
	0.0006183047704577434f,  0.0006162570317670083f,
	0.000614210803063415f,   0.0006121661144005574f,
	0.0006101229956925222f,  0.0006080814767133276f,
	0.0006060415870963706f,  0.000604003356333882f,
	0.0006019668137763886f,  0.0005999319886321841f,
	0.0005978989099668079f,  0.0005958676067025307f,
	0.0005938381076178495f,  0.0005918104413469892f,
	0.000589784636379413f,   0.0005877607210593397f,
	0.00058573872358527f,    0.0005837186720095198f,
	0.0005817005942377617f,  0.0005796845180285745f,
	0.0005776704709929999f,  0.000575658480594108f,
	0.0005736485741465703f,  0.0005716407788162399f,
	0.0005696351216197404f,  0.0005676316294240623f,
	0.0005656303289461672f,  0.0005636312467525995f,
	0.000561634409259107f,   0.0005596398427302676f,
	0.0005576475732791258f,  0.0005556576268668348f,
	0.0005536700293023084f,  0.0005516848062418796f,
	0.0005497019831889666f,  0.0005477215854937475f,
	0.0005457436383528425f,  0.0005437681668090032f,
	0.00054179519575081f,    0.0005398247499123779f,
	0.0005378568538730684f,  0.0005358915320572108f,
	0.0005339288087338299f,  0.0005319687080163818f,
	0.0005300112538624975f,  0.0005280564700737338f,
	0.0005261043802953321f,  0.0005241550080159845f,
	0.0005222083765676076f,  0.0005202645091251241f,
	0.0005183234287062513f,  0.0005163851581712975f,
	0.0005144497202229664f,  0.000512517137406168f,
	0.0005105874321078379f,  0.0005086606265567628f,
	0.0005067367428234152f,  0.000504815802819794f,
	0.0005028978282992731f,  0.0005009828408564572f,
	0.0004990708619270454f,  0.0004971619127877013f,
	0.0004952560145559311f,  0.000493353188189969f,
	0.0004914534544886691f,  0.0004895568340914056f,
	0.00048766334747797884f, 0.00048577301496853075f,
	0.00048388585672346445f, 0.0004820018927433742f,
	0.00048012114286897963f, 0.00047824362678106915f,
	0.00047636936400044906f, 0.0004744983738879011f,
	0.0004726306756441451f,  0.0004707662883098108f,
	0.0004689052307654148f,  0.00046704752173134563f,
	0.00046519317976785515f, 0.00046334222327505724f,
	0.00046149467049293283f, 0.00045965053950134234f,
	0.0004578098482200447f,  0.00045597261440872276f,
	0.0004541388556670164f,  0.00045230858943456106f,
	0.0004504818329910343f,  0.00044865860345620823f,
	0.00044683891779000835f, 0.0004450227927925803f,
	0.00044321024510436127f, 0.0004414012912061597f,
	0.0004395959474192403f,  0.00043779422990541657f,
	0.00043599615466714846f, 0.0004342017375476481f,
	0.00043241099423099017f, 0.00043062394024223025f,
	0.00042884059094752826f, 0.00042706096155427885f,
	0.0004252850671112479f,  0.00042351292250871495f,
	0.00042174454247862256f, 0.0004199799415947311f,
	0.00041821913427278f,    0.0004164621347706548f,
	0.0004147089571885609f,  0.00041295961546920264f,
	0.0004112141233979685f,  0.0004094724946031232f,
	0.0004077347425560038f,  0.00040600088057122363f,
	0.000404270921806881f,   0.0004025448792647741f,
	0.0004008227657906213f,  0.0003991045940742877f,
	0.000397390376650017f,   0.00039568012589666937f,
	0.0003939738540379645f,  0.0003922715731427308f,
	0.0003905732951251595f,  0.0003888790317450652f,
	0.00038718879460815077f, 0.0003855025951662786f,
	0.0003838204447177471f,  0.0003821423544075719f,
	0.0003804683352277734f,  0.0003787983980176689f,
	0.00037713255346417024f, 0.0003754708121020866f,
	0.0003738131843144328f,  0.00037215968033274186f,
	0.00037051031023738374f, 0.0003688650839578888f,
	0.0003672240112732754f,  0.0003655871018123844f,
	0.00036395436505421623f, 0.00036232581032827495f,
	0.00036070144681491607f, 0.0003590812835456994f,
	0.0003574653294037468f,  0.0003558535931241044f,
	0.00035424608329411033f, 0.00035264280835376583f,
	0.00035104377659611233f, 0.0003494489961676122f,
	0.00034785847506853425f, 0.0003462722211533439f,
	0.0003446902421310982f,  0.00034311254556584415f,
	0.00034153913887702243f, 0.00033997002933987524f,
	0.00033840522408585817f, 0.00033684473010305656f,
	0.00033528855423660604f, 0.00033373670318911724f,
	0.00033218918352110477f, 0.00033064600165141997f,
	0.0003291071638576881f,  0.0003275726762767491f,
	0.0003260425449051033f,  0.0003245167755993595f,
	0.00032299537407668827f, 0.00032147834591527867f,
	0.0003199656965547987f,  0.0003184574312968597f,
	0.0003169535553054838f,  0.00031545407360757653f,
	0.00031395899109340134f, 0.00031246831251705904f,
	0.0003109820424969701f,  0.0003095001855163607f,
	0.0003080227459237523f,  0.0003065497279334545f,
	0.00030508113562606134f, 0.0003036169729489512f,
	0.0003021572437167896f,  0.0003007019516120354f,
	0.00029925110018545075f, 0.00029780469285661305f,
	0.00029636273291443134f, 0.0002949252235176653f,
	0.0002934921676954467f,  0.0002920635683478048f,
	0.0002906394282461945f,  0.0002892197500340267f,
	0.0002878045362272028f,  0.00028639378921465063f,
	0.00028498751125886483f, 0.00028358570449644826f,
	0.00028218837093865756f, 0.00028079551247195053f,
	0.00027940713085853653f, 0.0002780232277369296f,
	0.0002766438046225036f,  0.0002752688629080503f,
	0.00027389840386434026f, 0.0002725324286406854f,
	0.0002711709382655042f,  0.0002698139336468898f,
	0.0002684614155731799f,  0.00026711338471352864f,
	0.0002657698416184818f,  0.0002644307867205529f,
	0.0002630962203348026f,  0.00026176614265941903f,
	0.0002604405537763016f,  0.0002591194536516455f,
	0.00025780284213652914f, 0.00025649071896750305f,
	0.0002551830837671807f,  0.00025387993604483164f,
	0.00025258127519697576f, 0.0002512871005079801f,
	0.0002499974111506568f,  0.00024871220618686316f,
	0.0002474314845681031f,  0.00024615524513613043f,
	0.00024488348662355357f, 0.0002436162076544422f,
	0.0002423534067449348f,  0.0002410950823038482f,
	0.0002398412326332884f,  0.0002385918559292624f,
	0.0002373469502822924f,  0.0002361065136780301f,
	0.00023487054399787318f, 0.00023363903901958246f,
	0.0002324119964179008f,  0.00023118941376517254f,
	0.00022997128853196493f, 0.00022875761808768938f,
	0.00022754839970122527f, 0.00022634363054154346f,
	0.00022514330767833167f, 0.0002239474280826204f,
	0.0002227559886274098f,  0.0002215689860882974f,
	0.00022038641714410676f, 0.00021920827837751695f,
	0.00021803456627569263f, 0.00021686527723091477f,
	0.00021570040754121254f, 0.0002145399534109953f,
	0.00021338391095168552f, 0.000212232276182352f,
	0.00021108504503034422f, 0.00020994221333192622f,
	0.0002088037768329122f,  0.00020766973118930125f,
	0.0002065400719679135f,  0.0002054147946470262f,
	0.00020429389461700995f, 0.00020317736718096589f,
	0.00020206520755536224f, 0.00020095741087067188f,
	0.00019985397217200978f, 0.00019875488641977028f,
	0.0001976601484902653f,  0.00019656975317636186f,
	0.00019548369518812008f, 0.00019440196915343095f,
	0.00019332456961865453f, 0.00019225149104925746f,
	0.00019118272783045118f, 0.00019011827426782926f,
	0.000189058124588005f,   0.0001880022729392493f,
	0.0001869507133921271f,  0.00018590343994013506f,
	0.00018486044650033783f, 0.00018382172691400444f,
	0.00018278727494724489f, 0.00018175708429164525f,
	0.00018073114856490344f, 0.0001797094613114639f,
	0.00017869201600315235f, 0.00017767880603980954f,
	0.00017666982474992494f, 0.0001756650653912695f,
	0.00017466452115152834f, 0.00017366818514893232f,
	0.00017267605043288928f, 0.0001716881099846147f,
	0.00017070435671776132f, 0.0001697247834790485f,
	0.00016874938304889053f, 0.0001677781481420242f,
	0.00016681107140813572f, 0.00016584814543248687f,
	0.00016488936273653982f, 0.0001639347157785818f,
	0.00016298419695434825f, 0.00016203779859764544f,
	0.00016109551298097182f, 0.00016015733231613868f,
	0.00015922324875488963f, 0.00015829325438951897f,
	0.0001573673412534893f,  0.00015644550132204771f,
	0.00015552772651284107f, 0.00015461400868653006f,
	0.0001537043396474021f,  0.0001527987111439832f,
	0.00015189711486964834f, 0.0001509995424632308f,
	0.00015010598550963024f, 0.00014921643554041943f,
	0.00014833088403444974f, 0.00014744932241845504f,
	0.00014657174206765485f, 0.0001456981343063553f,
	0.00014482849040854944f, 0.00014396280159851568f,
	0.00014310105905141488f, 0.00014224325389388604f,
	0.00014138937720464055f, 0.0001405394200150548f,
	0.00013969337330976117f, 0.0001388512280272379f,
	0.00013801297506039692f, 0.00013717860525717018f,
	0.0001363481094210947f,  0.0001355214783118956f,
	0.00013469870264606754f, 0.00013387977309745478f,
	0.0001330646802978291f,  0.0001322534148374664f,
	0.00013144596726572138f, 0.00013064232809160045f,
	0.00012984248778433283f, 0.00012904643677394027f,
	0.00012825416545180426f, 0.00012746566417123204f,
	0.00012668092324802043f, 0.00012589993296101794f,
	0.00012512268355268497f, 0.00012434916522965206f,
	0.00012357936816327622f, 0.00012281328249019564f,
	0.0001220508983128818f,  0.00012129220570019042f,
	0.00012053719468790977f, 0.00011978585527930736f,
	0.00011903817744567448f, 0.00011829415112686875f,
	0.00011755376623185465f, 0.00011681701263924195f,
	0.00011608388019782207f, 0.00011535435872710247f,
	0.00011462843801783876f, 0.0001139061078325648f,
	0.00011318735790612071f, 0.00011247217794617871f,
	0.00011176055763376668f, 0.00011105248662378983f,
	0.0001103479545455498f,  0.00010964695100326206f,
	0.00010894946557657059f, 0.00010825548782106077f,
	0.00010756500726876972f, 0.00010687801342869465f,
	0.00010619449578729878f, 0.00010551444380901503f,
	0.00010483784693674755f, 0.00010416469459237078f,
	0.00010349497617722636f, 0.00010282868107261763f,
	0.00010216579864030194f, 0.0001015063182229804f,
	0.00010085022914478556f, 0.00010019752071176654f,
	9.954818221237193e-05f,  9.890220291793011e-05f,
	9.825957208312758e-05f,  9.762027894648446e-05f,
	9.69843127308279e-05f,   9.635166264376294e-05f,
	9.572231787814095e-05f,  9.509626761252581e-05f,
	9.447350101165743e-05f,  9.385400722691298e-05f,
	9.323777539676566e-05f,  9.262479464724095e-05f,
	9.201505409237047e-05f,  9.140854283464327e-05f,
	9.080524996545484e-05f,  9.02051645655534e-05f,
	8.960827570548386e-05f,  8.901457244602923e-05f,
	8.842404383864955e-05f,  8.783667892591827e-05f,
	8.725246674195616e-05f,  8.667139631286269e-05f,
	8.609345665714492e-05f,  8.55186367861437e-05f,
	8.494692570445762e-05f,  8.437831241036419e-05f,
	8.381278589623846e-05f,  8.325033514896932e-05f,
	8.269094915037303e-05f,  8.213461687760425e-05f,
	8.158132730356457e-05f,  8.103106939730845e-05f,
	8.048383212444648e-05f,  7.993960444754626e-05f,
	7.939837532653057e-05f,  7.886013371907297e-05f,
	7.832486858099092e-05f,  7.779256886663615e-05f,
	7.726322352928267e-05f,  7.673682152151189e-05f,
	7.621335179559551e-05f,  7.569280330387546e-05f,
	7.517516499914157e-05f,  7.466042583500627e-05f,
	7.41485747662772e-05f,   7.363960074932669e-05f,
	7.313349274245897e-05f,  7.263023970627474e-05f,
	7.212983060403301e-05f,  7.163225440201041e-05f,
	7.113750006985803e-05f,  7.064555658095533e-05f,
	7.015641291276181e-05f,  6.967005804716589e-05f,
	6.918648097083109e-05f,  6.870567067553986e-05f,
	6.822761615853462e-05f,  6.775230642285623e-05f,
	6.727973047767991e-05f,  6.680987733864851e-05f,
	6.63427360282032e-05f,   6.587829557591156e-05f,
	6.541654501879306e-05f,  6.495747340164198e-05f,
	6.450106977734768e-05f,  6.404732320721233e-05f,
	6.359622276126601e-05f,  6.314775751857927e-05f,
	6.270191656757305e-05f,  6.225868900632599e-05f,
	6.181806394287934e-05f,  6.138003049553897e-05f,
	6.094457779317517e-05f,  6.051169497551961e-05f,
	6.00813711934598e-05f,   5.965359560933104e-05f,
	5.9228357397205746e-05f, 5.880564574318026e-05f,
	5.8385449845659025e-05f, 5.796775891563632e-05f,
	5.7552562176975315e-05f, 5.713984886668474e-05f,
	5.6729608235192814e-05f, 5.632182954661883e-05f,
	5.5916502079042083e-05f, 5.551361512476828e-05f,
	5.511315799059353e-05f,  5.471511999806562e-05f,
	5.431949048374301e-05f,  5.392625879945112e-05f,
	5.35354143125362e-05f,   5.314694640611669e-05f,
	5.276084447933215e-05f,  5.237709794758952e-05f,
	5.19956962428071e-05f,   5.161662881365591e-05f,
	5.1239885125798666e-05f, 5.086545466212622e-05f,
	5.049332692299159e-05f,  5.0123491426441486e-05f,
	4.9755937708445445e-05f, 4.939065532312249e-05f,
	4.9027633842965314e-05f, 4.866686285906209e-05f,
	4.8308331981315904e-05f, 4.79520308386616e-05f,
	4.759794907928037e-05f,  4.72460763708119e-05f,
	4.689640240056411e-05f,  4.654891687572043e-05f,
	4.620360952354487e-05f,  4.586047009158455e-05f,
	4.551948834786987e-05f,  4.51806540811125e-05f,
	4.484395710090073e-05f,  4.4509387237892716e-05f,
	4.4176934344007294e-05f, 4.38465882926124e-05f,
	4.351833897871131e-05f,  4.3192176319126416e-05f,
	4.2868090252680794e-05f, 4.254607074037743e-05f,
	4.222610776557618e-05f,  4.1908191334168384e-05f,
	4.1592311474749283e-05f, 4.127845823878813e-05f,
	4.096662170079602e-05f,  4.065679195849154e-05f,
	4.034895913296406e-05f,  4.004311336883492e-05f,
	3.973924483441631e-05f,  3.9437343721867966e-05f,
	3.913740024735161e-05f,  3.883940465118327e-05f,
	3.8543347197983336e-05f, 3.8249218176824486e-05f,
	3.795700790137745e-05f,  3.7666706710054485e-05f,
	3.7378304966150905e-05f, 3.709179305798428e-05f,
	3.680716139903159e-05f,  3.6524400428064247e-05f,
	3.6243500609281e-05f,    3.5964452432438664e-05f,
	3.5687246412980893e-05f, 3.541187309216471e-05f,
	3.513832303718507e-05f,  3.486658684129728e-05f,
	3.4596655123937424e-05f, 3.432851853084069e-05f,
	3.4062167734157666e-05f, 3.379759343256864e-05f,
	3.3534786351395824e-05f, 3.327373724271359e-05f,
	3.301443688545678e-05f,  3.275687608552686e-05f,
	3.2501045675896265e-05f, 3.224693651671066e-05f,
	3.199453949538931e-05f,  3.174384552672346e-05f,
	3.1494845552972766e-05f, 3.124753054395985e-05f,
	3.10018914971629e-05f,   3.075791943780631e-05f,
	3.0515605418949563e-05f, 3.0274940521574076e-05f,
	3.0035915854668234e-05f, 2.9798522555310568e-05f,
	2.956275178875107e-05f,  2.9328594748490617e-05f,
	2.9096042656358626e-05f, 2.8865086762588832e-05f,
	2.863571834589328e-05f,  2.8407928713534483e-05f,
	2.8181709201395842e-05f, 2.7957051174050224e-05f,
	2.7733946024826778e-05f, 2.7512385175876048e-05f,
	2.7292360078233227e-05f, 2.70738622118798e-05f,
	2.6856883085803334e-05f, 2.6641414238055632e-05f,
	2.6427447235809174e-05f, 2.6214973675411795e-05f,
	2.600398518243975e-05f,  2.5794473411749083e-05f,
	2.558643004752529e-05f,  2.5379846803331397e-05f,
	2.517471542215435e-05f,  2.4971027676449777e-05f,
	2.476877536818512e-05f,  2.456795032888122e-05f,
	2.436854441965219e-05f,  2.417054953124383e-05f,
	2.3973957584070346e-05f, 2.3778760528249574e-05f,
	2.3584950343636637e-05f, 2.3392519039856026e-05f,
	2.32014586563322e-05f,   2.3011761262318625e-05f,
	2.2823418956925272e-05f, 2.2636423869144704e-05f,
	2.2450768157876592e-05f, 2.226644401195079e-05f,
	2.2083443650148918e-05f, 2.190175932122451e-05f,
	2.1721383303921715e-05f, 2.154230790699254e-05f,
	2.1364525469212685e-05f, 2.1188028359395976e-05f,
	2.1012808976407376e-05f, 2.0838859749174576e-05f,
	2.0666173136698305e-05f, 2.0494741628061145e-05f,
	2.032455774243507e-05f,  2.0155614029087622e-05f,
	1.9987903067386716e-05f, 1.982141746680416e-05f,
	1.965614986691784e-05f,  1.9492092937412597e-05f,
	1.932923937807982e-05f,  1.9167581918815738e-05f,
	1.900711331961848e-05f,  1.8847826370583817e-05f,
	1.8689713891899704e-05f, 1.8532768733839542e-05f,
	1.837698377675424e-05f,  1.822235193106304e-05f,
	1.8068866137243162e-05f, 1.7916519365818194e-05f,
	1.776530461734536e-05f,  1.761521492240158e-05f,
	1.7466243341568363e-05f, 1.7318382965415564e-05f,
	1.7171626914483957e-05f, 1.702596833926673e-05f,
	1.6881400420189824e-05f, 1.6737916367591145e-05f,
	1.659550942169872e-05f,  1.6454172852607717e-05f,
	1.63138999602564e-05f,   1.6174684074401035e-05f,
	1.6036518554589693e-05f, 1.5899396790135042e-05f,
	1.5763312200086077e-05f, 1.562825823319883e-05f,
	1.549422836790605e-05f,  1.5361216112285908e-05f,
	1.5229215004029645e-05f, 1.509821861040829e-05f,
	1.496822052823837e-05f,  1.4839214383846656e-05f,
	1.4711193833033956e-05f, 1.4584152561037957e-05f,
	1.4458084282495131e-05f, 1.4332982741401709e-05f,
	1.4208841711073753e-05f, 1.4085654994106304e-05f,
	1.3963416422331627e-05f, 1.3842119856776597e-05f,
	1.3721759187619184e-05f, 1.3602328334144067e-05f,
	1.3483821244697416e-05f, 1.3366231896640793e-05f,
	1.3249554296304238e-05f, 1.313378247893852e-05f,
	1.3018910508666564e-05f};