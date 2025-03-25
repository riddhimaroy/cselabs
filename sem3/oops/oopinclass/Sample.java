interface Gift{void present(); }
interface Guest{ boolean present(); }
interface Presentable extends Gift, Guest{}