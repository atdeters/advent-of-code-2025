fn main() {
    // === Parse input file into to different vectors (ranges and ids) ===
    let input = include_str!("../../../input/input.txt");
    let mut id_ranges: Vec<&str> = input.split('\n').collect();
    id_ranges.pop();
    let mut all_ids: Vec<&str> = Vec::new();
    for (idx, range) in id_ranges.iter().enumerate() {
        if range.is_empty() {
            all_ids = id_ranges.split_off(idx + 1);
            id_ranges.pop();
            break;
        }
    }

    // === Make a vector of the values in between which IDs are fresh ===
    let mut tupes: Vec<(u64, u64)> = Vec::new();
    for range in &id_ranges {
        let parts: Vec<&str> = range.split('-').collect();
        let start: u64 = parts.first().unwrap().parse().unwrap();
        let end: u64 = parts.last().unwrap().parse().unwrap();
        tupes.push((start, end));
    }

    // === Count all IDs that are part of the ranges === 
    let mut fresh_ingredients: u32 = 0;
    for id in &all_ids {
        let tmp_id: u64 = id.parse().unwrap();
        for tupe in &tupes {
            if tmp_id >= tupe.0 && tmp_id <= tupe.1 {
                fresh_ingredients += 1;
                break;
            }
        }
    }
    println!("There are {fresh_ingredients} fresh ingredients available");
}
