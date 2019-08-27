use crate::chess::Board;
use std::collections::HashMap;

struct Evaluation;

#[derive(Default)]
pub struct Cache {
    hashmap: HashMap<Board, Evaluation>,
}

impl Cache {
    pub fn clear(&mut self) {
        self.hashmap.clear();
    }
}
