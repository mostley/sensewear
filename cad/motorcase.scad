/*motor_length = 16;
motor_width = 6;
motor_height = 5;*/

motor_length = 19;
motor_width = 6.5;
motor_height = 6;

case_strength = 1;

case_margin = 0.1;

module mounting_plate()
{
	union()
	{
		difference()
		{
			translate([case_strength, 0, 0])
			minkowski($fn=50)
			{
				cube([motor_length + case_strength * 2 + case_margin * 2 - case_strength*2, motor_width, case_strength/2]);
				cylinder(r=case_strength, h=case_strength/2);
			}

			translate([(motor_length * 0.125) + case_strength * 1.5 + case_margin, motor_width/4 + case_strength/2, -case_strength/2])
			minkowski($fn=50)
			{
				cube([motor_length * 0.75 - case_strength, motor_width/2 - case_strength/2, case_strength * 2]);
				cylinder(r=case_strength, h=case_strength);
			}
		}
	}
}

module case()
{
	union() {
		// bottom
		union() {
			cube([motor_length + case_strength * 2 + case_margin * 2, motor_width + case_strength * 2 + case_margin * 2, case_strength]);

			translate([0, motor_width + case_strength * 2 + case_margin * 2, 0])
			mounting_plate();

			translate([0, 0, 0])
			scale([1, -1, 1])
			mounting_plate();
		}

		// front wall
		translate([0, 0, case_strength])
		cube([case_strength, motor_width + case_strength * 2 + case_margin * 2, motor_height + case_strength + case_margin]);

		// back wall
		translate([motor_length + case_strength + case_margin * 2, 0, case_strength])
		difference()
		{
			cube([case_strength, motor_width + case_strength * 2 + case_margin * 2, motor_height + case_strength + case_margin]);

			translate([-case_strength/2, case_strength, 0])
			cube([case_strength*2, motor_width/2, motor_height * 0.75]);
		}

		// side wall right
		translate([case_strength, 0, case_strength])
		cube([motor_length + case_margin * 2, case_strength, motor_height + case_strength + case_margin]);

		// side wall left
		translate([case_strength, motor_width + case_strength + case_margin * 2, case_strength])
		cube([motor_length + case_margin * 2, case_strength, motor_height + case_strength + case_margin]);
	}
}

module case_cap()
{
	union() {
		// Top part
		translate([0, 0, case_strength])
		cube([motor_length + case_strength * 2 + case_margin * 2, motor_width + case_strength * 2 + case_margin * 2, case_strength]);

		// insert
		translate([case_strength + case_margin, case_strength + case_margin, case_margin])
		cube([motor_length, motor_width, case_strength - case_margin]);
	}
}

module motor_dummy()
{
	cube([motor_length, motor_width, motor_height]);
}

case();

//translate([0, 0, motor_height + case_strength + case_margin * 2])
//%case_cap();

//rotate([180, 0, 0])
//translate([0, -(motor_width + case_strength * 2 + case_margin * 2), -(case_strength*2)])
//case_cap();

//translate([case_strength + case_margin, case_strength + case_margin, case_strength + case_margin])
//motor_dummy();