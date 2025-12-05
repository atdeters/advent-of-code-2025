fn main() {
    // === Parse input file to get all the ranges ===
    let input = include_str!("../../../input/input.txt");
    let mut id_ranges: Vec<&str> = input.split('\n').collect();
    id_ranges.pop();
    for (idx, range) in id_ranges.iter().enumerate() {
        if range.is_empty() {
            id_ranges.truncate(idx);
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

    tupes.sort();

    let mut unique_ranges: Vec<(u64, u64)> = Vec::new();
    // === Combine overlapping ranges ===
    let mut start: u64 = 0;
    let mut end: u64 = 0;
    for tupe in &tupes {
        if tupe.0 > end {
            if start != 0 && end != 0 {
                unique_ranges.push((start, end));
            }
            start = tupe.0;
        }
        if tupe.1 > end {
            end = tupe.1;
        }
    }
    unique_ranges.push((start, end));

    // === Calculate nb of ids per range ===
    let mut result: u128 = 0;
    for range in unique_ranges {
        result += range.1  as u128 - range.0 as u128 + 1;
    }

    println!("There are {result} fresh ingredients")
}
