enum bone : int {
	Head = 110,
	Neck = 66,
	Chest = 37,
	Pelvis = 2,
	LShoulder = 9,
	LElbow = 10,
	LHand = 11,
	RShoulder = 38,
	RElbow = 39,
	RHand = 40,
	LHip = 71,
	LKnee = 72,
	LFoot = 73,
	RHip = 78,
	RKnee = 79,
	RFoot = 82,
	Root = 0
};

enum offset {
	uworld = 0x12D17A08,
	game_instance = 0x1F0,
	game_state = 0x178,
	local_player = 0x38,
	player_controller = 0x30,
	acknowledged_pawn = 0x350,
	aactor = 0xa0,
	skeletal_mesh = 0x328,
	player_state = 0x2b0,
	root_component = 0x1B0,
	velocity = 0x168,
	relative_location = 0x120,
	relative_rotation = 0x130,
	current_weapon = 0x9d8,
	weapon_data = 0x568,
	tier = 0x9b,
	team_index = 0x1239,
	player_array = 0x2c0,
	pawn_private = 0x320,
	component_to_world = 0x1c0,
	bone_array = 0x580,
	bone_cache = 0x5B8,
	TargetedFortPawn = 0x18e8, //https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerController&member=TargetedFortPawn
};




