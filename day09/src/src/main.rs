use std::cmp;
use std::fs;

fn area(p1: (i64, i64), p2: (i64, i64)) -> i64 {
    let x = (p1.0 - p2.0).abs() + 1;
    let y = (p1.1 - p2.1).abs() + 1;
    x * y
}

fn pt_in_rec(ptf: (i64, i64), p1: (i64, i64), p2: (i64, i64)) -> bool {
    if (ptf.0 >= cmp::min(p1.0, p2.0) && ptf.0 <= cmp::max(p1.0, p2.0))
        && (ptf.1 >= cmp::min(p1.1, p2.1) && ptf.1 <= cmp::max(p1.1, p2.1))
    {
        return true;
    }
    false
}

fn pt_inin_rec(ptf: (i64, i64), p1: (i64, i64), p2: (i64, i64)) -> bool {
    if (ptf.0 > cmp::min(p1.0, p2.0) && ptf.0 < cmp::max(p1.0, p2.0))
        && (ptf.1 > cmp::min(p1.1, p2.1) && ptf.1 < cmp::max(p1.1, p2.1))
    {
        return true;
    }
    false
}

/*
fn distance(p1: (i64,i64), p2: (i64,i64)) -> f64 {
	f64::sqrt((i64::pow(p1.0 - p2.0,2) + i64::pow(p1.1 - p2.1,2)) as f64)
}

fn closest_corner(grid_x: i64, grid_y: i64, p: (i64,i64)) -> (i64,i64) {
	let d1 = distance(p, (1,1));
	let d2 = distance(p, (grid_x,1));
	let d3 = distance(p, (1,grid_y));
	let d4 = distance(p, (grid_x,grid_y));
	if d1 < d2 && d1 < d3 && d1 < d4 {
		return (1,1)
	}
	else if d2 < d1 && d2 < d3 && d2 < d4 {
		return (grid_x, 1);
	}
	else if d3 < d1 && d3 < d2 && d3 < d4 {
		return (1,grid_y);
	}
	(grid_x, grid_y)
}
*/

fn main() {
    // Parse input into a vector of points (tuples)
    let binding = fs::read_to_string("../input/example.txt").expect("There should be a file");
    let input: Vec<&str> = binding.lines().collect();
    let mut points: Vec<(i64, i64)> = vec![];
    let mut grid_x: i64 = 0;
    let mut grid_y: i64 = 0;
    for p in input {
        let tmp: Vec<&str> = p.split(',').collect();
        let pt: (i64, i64) = (
            tmp[0].parse().expect("Should be numeric"),
            tmp[1].parse().expect("Should be numeric"),
        );
        grid_x = cmp::max(grid_x, pt.0);
        grid_y = cmp::max(grid_y, pt.1);
        points.push(pt);
    }

	println!("x:{grid_x}y:{grid_y}");

    // Brute-force every possible combination and keeping track of the biggest
    let mut result = 0;
	let mut resp1: (i64,i64) = (0,0);
	let mut resp2: (i64,i64) = (0,0);
	let mut respm1: (i64,i64) = (0,0);
	let mut respm2: (i64,i64) = (0,0);
    for p1 in &points {
        for p2 in 1..points.len() {

			// Make mirror points
			let pm1 = ((*p1).0, points[p2].1);
			let pm2 = (points[p2].0, (*p1).1);
			// Check closest corner
			let mut c1: (i64,i64) = (0,0);
			let mut c2: (i64,i64) = (0,0);

			// Find the corner that "belongs" to the mirror points
			if p1.1 > pm1.1 && p1.0 > points[p2].0 {
				c1 = (grid_x,0);
				c2 = (0, grid_y);
			}
			else if p1.1 > pm1.1 {
				c1 = (0,0);
				c2 = (grid_x, grid_y);
			}
			else if p1.1 < pm1.1 && p1.0 > points[p2].0 {
				c1 = (grid_x, grid_y);
				c2 = (0,0);
			}
			else if p1.1 < pm1.1 {
				c1 = (0, grid_y);
				c2 = (grid_x,0);
			}

			// Check for a point in the rectangle [mirror point, corner]
			let mut m1good = false;
			let mut m2good = false;
			let mut other = false;
			for p in &points {
				if pt_in_rec(*p, pm1, c1) == true {
					m1good = true;
				}
				if pt_in_rec(*p, pm2, c2) == true {
					m2good = true;
				}
				if pt_inin_rec(*p, *p1, points[p2]) {
					other = true;
				}
			}
			if m1good && m2good && !other {
				result = cmp::max(result, area(*p1, points[p2]));
				resp1 = *p1;
				resp2 = points[p2];
				respm1 = pm1;
				respm2 = pm2;

			}
        }
    }
	// TODO: Showing (11,7);(2,3) shows truetrue but should be truefalse
	println!("From: p1:{:?}p2:{:?}pm1:{:?}pm2:{:?}]", resp1, resp2, respm1, respm2);
    println!("The maximum rectangle has an area of {}", result);
}
